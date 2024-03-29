"""@package docstring
small script to instruct cmake;
"""
import argparse, subprocess, os , pathlib, re, shutil, sys


def deleteFilesAndDirectoriesInDir(directoryToClean):
    """ @brief wrapper for shutil.rmtree function and for loop attention function also looks in invisible directory's use with care;
        @param directoryToClean path of directory to clean up;
    """
    print(os.getcwd())
    for root, dirs, files in os.walk(directoryToClean, topdown = False):
        for item in dirs:
            path = os.path.join(root,item)
            if(re.search('System Volume Information', path)) is None:
                shutil.rmtree(path)
    for root, dirs, files in os.walk(directoryToClean, topdown = False):
        for item in files:
            path = os.path.join(root,item)
            if(re.search('System Volume Information', path)) is None:
                os.remove(path)


def argParser():
    """ @brief argument parser defines selectable options;
        @return namespace args used to make options available;
    """
    parser = argparse.ArgumentParser(description="Build your charon as you like; all target builds contain debug information by default")
    debugGroupParser = parser.add_argument_group("CMake and ninja builder")
    debugGroupParser.add_argument("--windows", "-w", action="store_true", help="build charon client port for Windows")
    debugGroupParser.add_argument("--demo", "-d", action="store_true",help="build charon client show case demo for customers")
    debugGroupParser.add_argument("--release","-r", action="store_true",help="add this flag for release build")
    specialGroup = parser.add_argument_group("extra","optional features")
    specialGroup.add_argument("--tests", action="store_true", help="build Unit Tests via ceedling")
    specialGroup.add_argument("--cppcheck", action="store_true", help="run cppCheck to get a code analysis")
    specialGroup.add_argument("--doxygen", action="store_true", help="build code documentation via doxygen")
    input_args = [str.lower(x) for x in sys.argv[1:]]
    args = parser.parse_args(input_args)
    return args


def cmakeAndNinja(cmdStream,ninja):
    """ @brief will execute commandline to configure cmake and execute ninja or ceedling;
        @param cmdStream command to  execute in commandline;
        @param ninja True if ninja should be performed;
        @returns True if commandline execution was successful;
    """
    builder = "ninja"
    stream = subprocess.run(cmdStream, capture_output=True, text=True, check=False)
    output = stream.stdout
    finishedCmake = stream.returncode
    print(output,flush=True)
    if((ninja is True) and (finishedCmake == 0)):
        stream = subprocess.run(builder, capture_output=True, text=True, check=False)
        output = stream.stdout
        print(output)
        finishedNinja = stream.returncode
        if(finishedNinja != 0):
            return False
        return True
    if((ninja is False) and (finishedCmake == 0)):
        return True
    return False


def prepBuildFolder(buildType):
    """ @brief preparing build folder depending on buildtype if debug or release for cmake config;
        @param buildType defines which type of build will be used debug or release;
    """
    if(buildType):
        neededWorkspace = "build\\CMakeReleaseBuild"
    else:
        neededWorkspace = "build\\CMakeDebugBuild"
    cmakeCache = "CMakeCache.txt"
    cmakeCacheFolder = "CMakeFiles"
    if(os.path.isdir(neededWorkspace) is False):
        print("build folder does not exist and will be created")
        pathlib.Path(neededWorkspace).mkdir(parents=True,exist_ok=True)
    tem = os.getcwd() 
    if(tem is not neededWorkspace):
        os.chdir(neededWorkspace)
    if(os.path.isdir(cmakeCacheFolder) is True):
        deleteFilesAndDirectoriesInDir(cmakeCacheFolder)
    if(os.path.isfile(cmakeCache) is True):
        os.remove(cmakeCache)


def buildRunner(preset: str, workspace, buildType: bool):
    """ @brief builder for different presets;
        @param preset chosen preset for ports;
        @param workspace current working directory;
        @param buildType defines which type of build will be used debug or release; 
    """
    presetStr = preset.lower()
    cmdStream = f"cmake ../../ --preset={presetStr}"
    if(buildType):
        cmdStream += " -DCMAKE_BUILD_TYPE=Release"
    prepBuildFolder(buildType)
    result = cmakeAndNinja(cmdStream,True)
    os.chdir(workspace)
    return result


def buildRunnerHelper(extra):
    """ @brief helper function to run ceedling ,cppcheck and doxygen; """
    cmdStream = None
    extra = extra.lower() 
    if(extra == "ceedling"):
        cmdStream = "ruby toolchain\\ceedling\\bin\\ceedling"
    if(extra == "cppcheck"):
        cmdStream = "codeanalysis.bat"
    if(extra == "doxygen"):
        cmdStream = "documentation.bat" 
    if(cmdStream == None):
        return False
    result = cmakeAndNinja(cmdStream,False)
    return result


def mainRunner():
    """ @brief main functions to check incoming arguments to call and reacts accordingly; """
    args = argParser()
    workspace = os.getcwd()
    try:
        if(args.windows is True):
            print("\nconfigure and build Windows Port\n")
            buildRunner("windows", workspace, args.release)
        if(args.demo is True):
            print("\nconfigure and build Demo Port\n")
            buildRunner("demo", workspace, args.release)
        if(args.tests is True):
            buildRunnerHelper("ceedling")
        if(args.doxygen is True):
            buildRunnerHelper("doxygen")
        if(args.cppcheck is True):
            buildRunnerHelper("cppcheck")
    except Exception as unwantedBehavior:
        print(unwantedBehavior)


if __name__ == "__main__":
    mainRunner()
