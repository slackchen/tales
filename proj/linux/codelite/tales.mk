##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=tales
ConfigurationName      :=Debug
WorkspacePath          := "/home/adrian/projects/tales/proj/linux/codelite"
ProjectPath            := "/home/adrian/projects/tales/proj/linux/codelite"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Adrian
Date                   :=20/01/17
CodeLitePath           :="/home/adrian/.codelite"
LinkerName             :=/usr/bin/g++
SharedObjectLinkerName :=/usr/bin/g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="tales.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  -lpthread
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)../../../src $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := /usr/bin/ar rcu
CXX      := /usr/bin/g++
CC       := /usr/bin/gcc
CXXFLAGS :=  -g -O0 -Wall -std=c++14 $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_tales.cpp$(ObjectSuffix) $(IntermediateDirectory)/core_object.cpp$(ObjectSuffix) $(IntermediateDirectory)/core_string.cpp$(ObjectSuffix) $(IntermediateDirectory)/net_socket.cpp$(ObjectSuffix) $(IntermediateDirectory)/Test_Test.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_tales.cpp$(ObjectSuffix): ../../../src/tales.cpp $(IntermediateDirectory)/src_tales.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/projects/tales/src/tales.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_tales.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_tales.cpp$(DependSuffix): ../../../src/tales.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_tales.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/src_tales.cpp$(DependSuffix) -MM "../../../src/tales.cpp"

$(IntermediateDirectory)/src_tales.cpp$(PreprocessSuffix): ../../../src/tales.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_tales.cpp$(PreprocessSuffix) "../../../src/tales.cpp"

$(IntermediateDirectory)/core_object.cpp$(ObjectSuffix): ../../../src/core/object.cpp $(IntermediateDirectory)/core_object.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/projects/tales/src/core/object.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_object.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_object.cpp$(DependSuffix): ../../../src/core/object.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_object.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core_object.cpp$(DependSuffix) -MM "../../../src/core/object.cpp"

$(IntermediateDirectory)/core_object.cpp$(PreprocessSuffix): ../../../src/core/object.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_object.cpp$(PreprocessSuffix) "../../../src/core/object.cpp"

$(IntermediateDirectory)/core_string.cpp$(ObjectSuffix): ../../../src/core/string.cpp $(IntermediateDirectory)/core_string.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/projects/tales/src/core/string.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/core_string.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/core_string.cpp$(DependSuffix): ../../../src/core/string.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/core_string.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/core_string.cpp$(DependSuffix) -MM "../../../src/core/string.cpp"

$(IntermediateDirectory)/core_string.cpp$(PreprocessSuffix): ../../../src/core/string.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/core_string.cpp$(PreprocessSuffix) "../../../src/core/string.cpp"

$(IntermediateDirectory)/net_socket.cpp$(ObjectSuffix): ../../../src/net/socket.cpp $(IntermediateDirectory)/net_socket.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/projects/tales/src/net/socket.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/net_socket.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/net_socket.cpp$(DependSuffix): ../../../src/net/socket.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/net_socket.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/net_socket.cpp$(DependSuffix) -MM "../../../src/net/socket.cpp"

$(IntermediateDirectory)/net_socket.cpp$(PreprocessSuffix): ../../../src/net/socket.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/net_socket.cpp$(PreprocessSuffix) "../../../src/net/socket.cpp"

$(IntermediateDirectory)/Test_Test.cpp$(ObjectSuffix): ../../../Test/Test.cpp $(IntermediateDirectory)/Test_Test.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/adrian/projects/tales/Test/Test.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Test_Test.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/Test_Test.cpp$(DependSuffix): ../../../Test/Test.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/Test_Test.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/Test_Test.cpp$(DependSuffix) -MM "../../../Test/Test.cpp"

$(IntermediateDirectory)/Test_Test.cpp$(PreprocessSuffix): ../../../Test/Test.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/Test_Test.cpp$(PreprocessSuffix) "../../../Test/Test.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


