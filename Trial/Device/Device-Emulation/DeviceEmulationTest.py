# /usr/bin/env python 

import unittest
from DeviceEmulation import *

class DeviceEmulationTest(unittest.TestCase):
    def setUp(self):
        unittest.TestCase.setUp(self)
    
    def tearDown(self):
        unittest.TestCase.tearDown(self)
    
    def testCase_01(self):
        pass

if __name__ == '__main__':
    unittest.main()
    