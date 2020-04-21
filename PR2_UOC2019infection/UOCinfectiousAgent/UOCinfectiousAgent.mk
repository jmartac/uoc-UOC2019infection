##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=UOCinfectiousAgent
ConfigurationName      :=Debug
WorkspacePath          :=/home/uoc/Documents/codelite/workspaces/UOC2019infection
ProjectPath            :=/home/uoc/Documents/codelite/workspaces/UOC2019infection/UOCinfectiousAgent
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=uoc
Date                   :=16/04/20
CodeLitePath           :=/home/uoc/.codelite
LinkerName             :=gcc
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=../lib/lib$(ProjectName).a
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="UOCinfectiousAgent.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). $(IncludeSwitch)./include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := gcc
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=$(IntermediateDirectory)/src_city.c$(ObjectSuffix) $(IntermediateDirectory)/src_country.c$(ObjectSuffix) $(IntermediateDirectory)/src_infection.c$(ObjectSuffix) $(IntermediateDirectory)/src_infectiousAgent.c$(ObjectSuffix) $(IntermediateDirectory)/src_reservoir.c$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "/home/uoc/Documents/codelite/workspaces/UOC2019infection/.build-debug"
	@echo rebuilt > "/home/uoc/Documents/codelite/workspaces/UOC2019infection/.build-debug/UOCinfectiousAgent"

MakeIntermediateDirs:
	@test -d ./Debug || $(MakeDirCommand) ./Debug


./Debug:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/src_city.c$(ObjectSuffix): src/city.c $(IntermediateDirectory)/src_city.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Documents/codelite/workspaces/UOC2019infection/UOCinfectiousAgent/src/city.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_city.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_city.c$(DependSuffix): src/city.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_city.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_city.c$(DependSuffix) -MM src/city.c

$(IntermediateDirectory)/src_city.c$(PreprocessSuffix): src/city.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_city.c$(PreprocessSuffix) src/city.c

$(IntermediateDirectory)/src_country.c$(ObjectSuffix): src/country.c $(IntermediateDirectory)/src_country.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Documents/codelite/workspaces/UOC2019infection/UOCinfectiousAgent/src/country.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_country.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_country.c$(DependSuffix): src/country.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_country.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_country.c$(DependSuffix) -MM src/country.c

$(IntermediateDirectory)/src_country.c$(PreprocessSuffix): src/country.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_country.c$(PreprocessSuffix) src/country.c

$(IntermediateDirectory)/src_infection.c$(ObjectSuffix): src/infection.c $(IntermediateDirectory)/src_infection.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Documents/codelite/workspaces/UOC2019infection/UOCinfectiousAgent/src/infection.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_infection.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_infection.c$(DependSuffix): src/infection.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_infection.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_infection.c$(DependSuffix) -MM src/infection.c

$(IntermediateDirectory)/src_infection.c$(PreprocessSuffix): src/infection.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_infection.c$(PreprocessSuffix) src/infection.c

$(IntermediateDirectory)/src_infectiousAgent.c$(ObjectSuffix): src/infectiousAgent.c $(IntermediateDirectory)/src_infectiousAgent.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Documents/codelite/workspaces/UOC2019infection/UOCinfectiousAgent/src/infectiousAgent.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_infectiousAgent.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_infectiousAgent.c$(DependSuffix): src/infectiousAgent.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_infectiousAgent.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_infectiousAgent.c$(DependSuffix) -MM src/infectiousAgent.c

$(IntermediateDirectory)/src_infectiousAgent.c$(PreprocessSuffix): src/infectiousAgent.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_infectiousAgent.c$(PreprocessSuffix) src/infectiousAgent.c

$(IntermediateDirectory)/src_reservoir.c$(ObjectSuffix): src/reservoir.c $(IntermediateDirectory)/src_reservoir.c$(DependSuffix)
	$(CC) $(SourceSwitch) "/home/uoc/Documents/codelite/workspaces/UOC2019infection/UOCinfectiousAgent/src/reservoir.c" $(CFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/src_reservoir.c$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/src_reservoir.c$(DependSuffix): src/reservoir.c
	@$(CC) $(CFLAGS) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/src_reservoir.c$(ObjectSuffix) -MF$(IntermediateDirectory)/src_reservoir.c$(DependSuffix) -MM src/reservoir.c

$(IntermediateDirectory)/src_reservoir.c$(PreprocessSuffix): src/reservoir.c
	$(CC) $(CFLAGS) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/src_reservoir.c$(PreprocessSuffix) src/reservoir.c


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


