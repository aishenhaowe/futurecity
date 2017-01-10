# /usr/bin/env python 

class DeviceManager(object):
    def __init__(self):
        self._internalList = []
    
    # Add a valid device into the list
    def AddDevice(self, device):
        if device is None or device in self._internalList or self.GetDevice(device.GetDeviceId()):
            return
        self._internalList.append(device)
    
    # Get a device through device id
    def GetDevice(self, deviceId):
        for dev in self._internalList:
            if deviceId == dev.GetDeviceId():
                return dev
        return None
    
    # Delete the device through device id
    def DeleteDevice(self, deviceId):
        dev = self.GetDevice(deviceId)
        
        if dev is not None:
            self._internalList.remove(dev)
            
    # Get the device count
    def GetCount(self):
        return len(self._internalList)