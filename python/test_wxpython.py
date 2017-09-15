#!/usr/bin/env python

import wx

application = wx.App()

frame = wx.Frame(None, wx.ID_ANY, u"testframe")
frame.Show()
application.MainLoop()
