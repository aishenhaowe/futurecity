# The environment file  

import re
from SCons.Script import *

class BuildType:
    SERVER              = 0
    ARM                 = 1
    LINT                = 2
    CXXTEST             = 3
    DOXYGEN             = 4
    ROBOT_TEST          = 5
    MAX_BUILD_TYPE      = 6
    
build_name = [None] * BuildType.MAX_BUILD_TYPE
build_name[BuildType.SERVER]            = 'server'
build_name[BuildType.ARM]               = 'arm'
build_name[BuildType.LINT]              = 'lint'
build_name[BuildType.CXXTEST]           = 'cxxtest'
build_name[BuildType.DOXYGEN]           = 'doxygen'
build_name[BuildType.ROBOT_TEST]        = 'robot_test'


class FcEnv:
    root = os.path.join(Dir('#').abspath)
    
    build_type              = BuildType.MAX_BUILD_TYPE
    build_defines           = []
    target_name             = ''
    
    @staticmethod
    def GetBuildType():
        return FcEnv.build_type
    
    @staticmethod
    def SetBuildType(build_type):
        FcEnv.build_type = build_type
        
    @staticmethod
    def GetTargetName():
        return FcEnv.target_name
        
    @staticmethod
    def GetBuildDefines():
        return FcEnv.build_defines
        
        
    @staticmethod
    def SetBuildInfo(info):
        FcEnv.SetBuildType(info['build_type'])
        #FcEnv.build_defines = info['defines']
        FcEnv.target_name = info['name']
        
        