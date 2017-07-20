# -*- coding:utf-8 -*-

from datetime import datetime
from string import Template

class DeltaTemplate(Template):
    delimiter = "%"

class Stopwatch:
    def __init__(self):
        self.reset()
    def reset(self):
        self.lastTime_ = self.startTime_ = datetime.now()
        self.count_ = 1
        self.isRunning_ = True
    def stop(self):
        if not self.isRunning_:
            return self.totalDur_
        self.totalDur_ = datetime.now() - self.startTime_
        self.isRunning_ = False
        return self.totalDur_
    def lap(self):
        now = datetime.now()
        diff = now - self.lastTime_
        self.lastTime_ = now
        self.count_ += 1
        return diff
    def getAverage(self):
        return self.totalDur_ / self.count_
    def report(self):
        if self.isRunning_:
            self.totalDur_ = datetime.now() - self.startTime_
        lap_str = ('', ' (Lap#' + str(self.count_) + ': ' + self.formatLap('%H:%M:%S.%f=%T s') + ')')[1 < self.count_]
        av_str  = ('', ' (Average: ' + self.formatAverage('%H:%M:%S.%f=%T s') + ')')[1 < self.count_]
        print('Duration:' + self.formatTotal('%H:%M:%S.%f=%T s') + lap_str + av_str)
    def stopAndReport(self):
        self.stop()
        self.report()
    def formatTotal(self, fmt):
        return self.strfdelta(self.totalDur_, fmt)
    def formatLap(self, fmt):
        return self.strfdelta(datetime.now() - self.lastTime_, fmt)
    def lapAndFormat(self, fmt):
        return self.strfdelta(self.lap(), fmt)
    def formatAverage(self, fmt):
        return self.strfdelta(self.getAverage(), fmt)
    def strfdelta(self, tdelta, fmt):
        d = {"D": tdelta.days}
        d["H"], rem = divmod(tdelta.seconds, 3600)
        d["M"], d["S"] = divmod(rem, 60)
        d["f"] = tdelta.microseconds/1000
        d["T"] = tdelta.total_seconds()
        t = DeltaTemplate(fmt)
        return t.substitute(**d) # thanks to http://stackoverflow.com/questions/8906926/formatting-python-timedelta-objects

# Test
if __name__ == '__main__':
    import time
    # 1. Start profiling
    watch = Stopwatch()
    for lap in range(20):
        for i in range(10):
            # Your heavy load here...
            time.sleep(0.01)
            # print lap time
            print('Laptime by custom format -->' + watch.lapAndFormat('%S.%f'))
        # report for now
        watch.report()
    # report finally
    watch.stopAndReport()
