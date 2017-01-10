# /usr/bin/env python 
from DeviceManager import DeviceManager
from Device import Device

class UserInterface(object):
    def __init__(self, deviceManager):
        self._deviceManager = deviceManager
    
    def CreateDevice(self, deviceId, deviceName):
        dev = Device(deviceId, deviceName)
        self._deviceManager.AddDevice(dev)
    
    def DeleteDevice(self, deviceId):
        self._deviceManager.DeleteDevice(deviceId)
    
    def GetDeviceCount(self):
        return self._deviceManager.GetCount()