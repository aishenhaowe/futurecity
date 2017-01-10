# /usr/bin/env python 

class Device(object):
    def __init__(self, deviveId, deviveName):
        self._deviveId = deviveId
        self._deviveName = deviveName
    
    # Get the device id, it's only
    def GetDeviceId(self):
        return self._deviveId
    
    def GetDeviveName(self):
        return self._deviceName;
    
    # Capture Data from sensor
    def CaptureData(self, captureData):
        self._captureData = captureData
        
    # Get the captured data, maybe will be used for debug
    def GetData(self):
        return self._captureData
    
    # Send data through CoAP interface
    def SendCoapData(self):
        pass