# /usr/bin/env python 

import unittest
from UserInterface import *

class DeviceEmulationTest(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
    
    def tearDown(self):
        unittest.TestCase.tearDown(self)
    
    def testCase_01(self):
        devManager = DeviceManager()
        ui = UserInterface(devManager)
        ui.CreateDevice(1, 'device1')
        ui.CreateDevice(2, 'device2')
        
        self.assertEqual(ui.GetDeviceCount(), 2)

    def testcase_02(self):
        devManager = DeviceManager()
        ui = UserInterface(devManager)
        ui.CreateDevice(1, 'device1')
        ui.CreateDevice(1, 'device2')
        
        self.assertEqual(ui.GetDeviceCount(), 1)

    def testcase_03(self):
        devManager = DeviceManager()
        ui = UserInterface(devManager)
        ui.CreateDevice(1, 'device1')
        ui.CreateDevice(2, 'device2')
        ui.DeleteDevice(1)
        
        self.assertEqual(ui.GetDeviceCount(), 1)
        
    def testcase_04(self):
        devManager = DeviceManager()
        ui = UserInterface(devManager)
        ui.CreateDevice(1, 'device1')
        ui.CreateDevice(2, 'device2')
        ui.DeleteDevice(3)
        
        self.assertEqual(ui.GetDeviceCount(), 2)

if __name__ == '__main__':
    unittest.main()
    