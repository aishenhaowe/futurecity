# /usr/bin/env python 

class Device(object):
    def __init__(self, devId):
        self._devId = devId
    
    # Get the device id, it's only
    def GetDevId(self):
        return self._dev_id
    
    # Capture Data from sensor
    def CaptureData(self, captureData):
        self._captureData = captureData
        
    # Get the captured data, maybe will be used for debug
    def GetData(self):
        return self._captureData
    
    # Send data through CoAP interface
    def SendCoapData(self):
        pass