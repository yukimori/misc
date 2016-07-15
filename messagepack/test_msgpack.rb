require 'msgpack'

datas = MessagePack.unpack(File.open("cpp_data.bin"))
datas2 = MessagePack.unpack(File.open("test_msg.bin"))
p datas
p datas2
