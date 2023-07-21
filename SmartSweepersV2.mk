##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=SmartSweepersV2
ConfigurationName      :=Release
WorkspaceConfiguration := $(ConfigurationName)
WorkspacePath          :=/home/john/Documents/Programming
ProjectPath            :=/home/john/Documents/Programming/SmartSweepersV2
IntermediateDirectory  :=../build-$(ConfigurationName)/SmartSweepersV2
OutDir                 :=../build-$(ConfigurationName)/SmartSweepersV2
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=
Date                   :=21/07/23
CodeLitePath           :=/home/john/.codelite
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
OutputFile             :=../build-$(ConfigurationName)/bin/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :=$(IntermediateDirectory)/ObjectsList.txt
PCHCompileFlags        :=
LinkOptions            :=  -lGL -lGLU -lSDL -pthread
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
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
CXXFLAGS :=  -O2 -Wall $(Preprocessors)
CFLAGS   :=  -O2 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := /usr/bin/as


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects0=../build-$(ConfigurationName)/SmartSweepersV2/Matrix3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Sphere.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/PhysicObject3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Cell3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/AxisAlignedBox3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/AxisAngle.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/DynamicIntersection.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Chromosome.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/CompareChromosome.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/CompareTestChromo.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Result.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/DefaultActivationFunction.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/GeneticAlgorithm.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/HyperbolicTangent.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/MyChromosome.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Parameters.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Population.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Range.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/RouletteWheel.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/Selector.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Sigmoid.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Statistics.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Layer.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Function.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Matrix.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/TestChromo.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Tournament.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Mine.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/SmartMineSweeper.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/RGBColor.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Plane.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Reserve.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Matrix2D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/World.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/SphereTree.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/NeuralNetwork.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Tank.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Solver.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrMine.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Graphics.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Vector.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Camera.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Vector3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Mean.cpp$(ObjectSuffix) 

Objects1=../build-$(ConfigurationName)/SmartSweepersV2/Intersectable.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/IsMovableNonMovablePair.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/TestCamera.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/Vector2D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Partition_Triangles.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Polygon.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesCenters.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/DefaultBrainEvolver.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Settings.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Triangle.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/DynamicSphere.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Covariance.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/Simulation.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/MTLLoader.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/MeshBuilder.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/GaussPointsFit.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Grid3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/TestWorldMesh.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesAreas.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Mobile.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Sensors.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/DynamicPlane.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/DefaultSteeringFunction.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/CompareMyChromosome.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Line.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/BoundingVolumeBuilder3D.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/NotClosestObjectException.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Octree.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Quaternion.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Indexes.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/Quad.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/TestIcosahedron.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/VTN.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/MaterialManager.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/LineSegment.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/GaussTrianglesFit.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Face.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/OBJ_Loader.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Gudermann.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/UnsupportedOperationException.cpp$(ObjectSuffix) 

Objects2=../build-$(ConfigurationName)/SmartSweepersV2/ComputeVertexList.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Rand.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3DTree.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Utility.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Intersection.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/TridiagonalForm.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/order_eigen_values.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Support.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Box.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/Brain.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Eigen.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/GraphicObject.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Application.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/OrientedEllipsoid.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/ModelIterator.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/ModelConstantIterator.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Model.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/main.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Renderer.cpp$(ObjectSuffix) \
	../build-$(ConfigurationName)/SmartSweepersV2/Material.cpp$(ObjectSuffix) ../build-$(ConfigurationName)/SmartSweepersV2/Mesh.cpp$(ObjectSuffix) 



Objects=$(Objects0) $(Objects1) $(Objects2) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: MakeIntermediateDirs $(OutputFile)

$(OutputFile): ../build-$(ConfigurationName)/SmartSweepersV2/.d $(Objects) 
	@mkdir -p "../build-$(ConfigurationName)/SmartSweepersV2"
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	@echo $(Objects1) >> $(ObjectsFileList)
	@echo $(Objects2) >> $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@mkdir -p "../build-$(ConfigurationName)/SmartSweepersV2"
	@mkdir -p ""../build-$(ConfigurationName)/bin""

../build-$(ConfigurationName)/SmartSweepersV2/.d:
	@mkdir -p "../build-$(ConfigurationName)/SmartSweepersV2"

PreBuild:


##
## Objects
##
../build-$(ConfigurationName)/SmartSweepersV2/Matrix3D.cpp$(ObjectSuffix): Matrix3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Matrix3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Matrix3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Matrix3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Matrix3D.cpp$(DependSuffix): Matrix3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Matrix3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Matrix3D.cpp$(DependSuffix) -MM Matrix3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Matrix3D.cpp$(PreprocessSuffix): Matrix3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Matrix3D.cpp$(PreprocessSuffix) Matrix3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Sphere.cpp$(ObjectSuffix): Sphere.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Sphere.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Sphere.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sphere.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Sphere.cpp$(DependSuffix): Sphere.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Sphere.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Sphere.cpp$(DependSuffix) -MM Sphere.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Sphere.cpp$(PreprocessSuffix): Sphere.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Sphere.cpp$(PreprocessSuffix) Sphere.cpp

../build-$(ConfigurationName)/SmartSweepersV2/PhysicObject3D.cpp$(ObjectSuffix): PhysicObject3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/PhysicObject3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/PhysicObject3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/PhysicObject3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/PhysicObject3D.cpp$(DependSuffix): PhysicObject3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/PhysicObject3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/PhysicObject3D.cpp$(DependSuffix) -MM PhysicObject3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/PhysicObject3D.cpp$(PreprocessSuffix): PhysicObject3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/PhysicObject3D.cpp$(PreprocessSuffix) PhysicObject3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Cell3D.cpp$(ObjectSuffix): Cell3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Cell3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Cell3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Cell3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Cell3D.cpp$(DependSuffix): Cell3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Cell3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Cell3D.cpp$(DependSuffix) -MM Cell3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Cell3D.cpp$(PreprocessSuffix): Cell3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Cell3D.cpp$(PreprocessSuffix) Cell3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/AxisAlignedBox3D.cpp$(ObjectSuffix): AxisAlignedBox3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/AxisAlignedBox3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/AxisAlignedBox3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AxisAlignedBox3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/AxisAlignedBox3D.cpp$(DependSuffix): AxisAlignedBox3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/AxisAlignedBox3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/AxisAlignedBox3D.cpp$(DependSuffix) -MM AxisAlignedBox3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/AxisAlignedBox3D.cpp$(PreprocessSuffix): AxisAlignedBox3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/AxisAlignedBox3D.cpp$(PreprocessSuffix) AxisAlignedBox3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/AxisAngle.cpp$(ObjectSuffix): AxisAngle.cpp ../build-$(ConfigurationName)/SmartSweepersV2/AxisAngle.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/AxisAngle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AxisAngle.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/AxisAngle.cpp$(DependSuffix): AxisAngle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/AxisAngle.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/AxisAngle.cpp$(DependSuffix) -MM AxisAngle.cpp

../build-$(ConfigurationName)/SmartSweepersV2/AxisAngle.cpp$(PreprocessSuffix): AxisAngle.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/AxisAngle.cpp$(PreprocessSuffix) AxisAngle.cpp

../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3D.cpp$(ObjectSuffix): OrientedBox3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/OrientedBox3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OrientedBox3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3D.cpp$(DependSuffix): OrientedBox3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3D.cpp$(DependSuffix) -MM OrientedBox3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3D.cpp$(PreprocessSuffix): OrientedBox3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3D.cpp$(PreprocessSuffix) OrientedBox3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DynamicIntersection.cpp$(ObjectSuffix): DynamicIntersection.cpp ../build-$(ConfigurationName)/SmartSweepersV2/DynamicIntersection.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/DynamicIntersection.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DynamicIntersection.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/DynamicIntersection.cpp$(DependSuffix): DynamicIntersection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/DynamicIntersection.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/DynamicIntersection.cpp$(DependSuffix) -MM DynamicIntersection.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DynamicIntersection.cpp$(PreprocessSuffix): DynamicIntersection.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/DynamicIntersection.cpp$(PreprocessSuffix) DynamicIntersection.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Chromosome.cpp$(ObjectSuffix): Chromosome.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Chromosome.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Chromosome.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Chromosome.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Chromosome.cpp$(DependSuffix): Chromosome.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Chromosome.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Chromosome.cpp$(DependSuffix) -MM Chromosome.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Chromosome.cpp$(PreprocessSuffix): Chromosome.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Chromosome.cpp$(PreprocessSuffix) Chromosome.cpp

../build-$(ConfigurationName)/SmartSweepersV2/CompareChromosome.cpp$(ObjectSuffix): CompareChromosome.cpp ../build-$(ConfigurationName)/SmartSweepersV2/CompareChromosome.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/CompareChromosome.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CompareChromosome.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/CompareChromosome.cpp$(DependSuffix): CompareChromosome.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/CompareChromosome.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/CompareChromosome.cpp$(DependSuffix) -MM CompareChromosome.cpp

../build-$(ConfigurationName)/SmartSweepersV2/CompareChromosome.cpp$(PreprocessSuffix): CompareChromosome.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/CompareChromosome.cpp$(PreprocessSuffix) CompareChromosome.cpp

../build-$(ConfigurationName)/SmartSweepersV2/CompareTestChromo.cpp$(ObjectSuffix): CompareTestChromo.cpp ../build-$(ConfigurationName)/SmartSweepersV2/CompareTestChromo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/CompareTestChromo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CompareTestChromo.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/CompareTestChromo.cpp$(DependSuffix): CompareTestChromo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/CompareTestChromo.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/CompareTestChromo.cpp$(DependSuffix) -MM CompareTestChromo.cpp

../build-$(ConfigurationName)/SmartSweepersV2/CompareTestChromo.cpp$(PreprocessSuffix): CompareTestChromo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/CompareTestChromo.cpp$(PreprocessSuffix) CompareTestChromo.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Result.cpp$(ObjectSuffix): Result.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Result.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Result.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Result.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Result.cpp$(DependSuffix): Result.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Result.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Result.cpp$(DependSuffix) -MM Result.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Result.cpp$(PreprocessSuffix): Result.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Result.cpp$(PreprocessSuffix) Result.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DefaultActivationFunction.cpp$(ObjectSuffix): DefaultActivationFunction.cpp ../build-$(ConfigurationName)/SmartSweepersV2/DefaultActivationFunction.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/DefaultActivationFunction.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DefaultActivationFunction.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/DefaultActivationFunction.cpp$(DependSuffix): DefaultActivationFunction.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/DefaultActivationFunction.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/DefaultActivationFunction.cpp$(DependSuffix) -MM DefaultActivationFunction.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DefaultActivationFunction.cpp$(PreprocessSuffix): DefaultActivationFunction.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/DefaultActivationFunction.cpp$(PreprocessSuffix) DefaultActivationFunction.cpp

../build-$(ConfigurationName)/SmartSweepersV2/GeneticAlgorithm.cpp$(ObjectSuffix): GeneticAlgorithm.cpp ../build-$(ConfigurationName)/SmartSweepersV2/GeneticAlgorithm.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/GeneticAlgorithm.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GeneticAlgorithm.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/GeneticAlgorithm.cpp$(DependSuffix): GeneticAlgorithm.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/GeneticAlgorithm.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/GeneticAlgorithm.cpp$(DependSuffix) -MM GeneticAlgorithm.cpp

../build-$(ConfigurationName)/SmartSweepersV2/GeneticAlgorithm.cpp$(PreprocessSuffix): GeneticAlgorithm.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/GeneticAlgorithm.cpp$(PreprocessSuffix) GeneticAlgorithm.cpp

../build-$(ConfigurationName)/SmartSweepersV2/HyperbolicTangent.cpp$(ObjectSuffix): HyperbolicTangent.cpp ../build-$(ConfigurationName)/SmartSweepersV2/HyperbolicTangent.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/HyperbolicTangent.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HyperbolicTangent.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/HyperbolicTangent.cpp$(DependSuffix): HyperbolicTangent.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/HyperbolicTangent.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/HyperbolicTangent.cpp$(DependSuffix) -MM HyperbolicTangent.cpp

../build-$(ConfigurationName)/SmartSweepersV2/HyperbolicTangent.cpp$(PreprocessSuffix): HyperbolicTangent.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/HyperbolicTangent.cpp$(PreprocessSuffix) HyperbolicTangent.cpp

../build-$(ConfigurationName)/SmartSweepersV2/MyChromosome.cpp$(ObjectSuffix): MyChromosome.cpp ../build-$(ConfigurationName)/SmartSweepersV2/MyChromosome.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/MyChromosome.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MyChromosome.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/MyChromosome.cpp$(DependSuffix): MyChromosome.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/MyChromosome.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/MyChromosome.cpp$(DependSuffix) -MM MyChromosome.cpp

../build-$(ConfigurationName)/SmartSweepersV2/MyChromosome.cpp$(PreprocessSuffix): MyChromosome.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/MyChromosome.cpp$(PreprocessSuffix) MyChromosome.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Parameters.cpp$(ObjectSuffix): Parameters.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Parameters.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Parameters.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Parameters.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Parameters.cpp$(DependSuffix): Parameters.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Parameters.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Parameters.cpp$(DependSuffix) -MM Parameters.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Parameters.cpp$(PreprocessSuffix): Parameters.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Parameters.cpp$(PreprocessSuffix) Parameters.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Population.cpp$(ObjectSuffix): Population.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Population.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Population.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Population.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Population.cpp$(DependSuffix): Population.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Population.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Population.cpp$(DependSuffix) -MM Population.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Population.cpp$(PreprocessSuffix): Population.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Population.cpp$(PreprocessSuffix) Population.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Range.cpp$(ObjectSuffix): Range.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Range.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Range.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Range.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Range.cpp$(DependSuffix): Range.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Range.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Range.cpp$(DependSuffix) -MM Range.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Range.cpp$(PreprocessSuffix): Range.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Range.cpp$(PreprocessSuffix) Range.cpp

../build-$(ConfigurationName)/SmartSweepersV2/RouletteWheel.cpp$(ObjectSuffix): RouletteWheel.cpp ../build-$(ConfigurationName)/SmartSweepersV2/RouletteWheel.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/RouletteWheel.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RouletteWheel.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/RouletteWheel.cpp$(DependSuffix): RouletteWheel.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/RouletteWheel.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/RouletteWheel.cpp$(DependSuffix) -MM RouletteWheel.cpp

../build-$(ConfigurationName)/SmartSweepersV2/RouletteWheel.cpp$(PreprocessSuffix): RouletteWheel.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/RouletteWheel.cpp$(PreprocessSuffix) RouletteWheel.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Selector.cpp$(ObjectSuffix): Selector.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Selector.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Selector.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Selector.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Selector.cpp$(DependSuffix): Selector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Selector.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Selector.cpp$(DependSuffix) -MM Selector.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Selector.cpp$(PreprocessSuffix): Selector.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Selector.cpp$(PreprocessSuffix) Selector.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Sigmoid.cpp$(ObjectSuffix): Sigmoid.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Sigmoid.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Sigmoid.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sigmoid.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Sigmoid.cpp$(DependSuffix): Sigmoid.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Sigmoid.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Sigmoid.cpp$(DependSuffix) -MM Sigmoid.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Sigmoid.cpp$(PreprocessSuffix): Sigmoid.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Sigmoid.cpp$(PreprocessSuffix) Sigmoid.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Statistics.cpp$(ObjectSuffix): Statistics.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Statistics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Statistics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Statistics.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Statistics.cpp$(DependSuffix): Statistics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Statistics.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Statistics.cpp$(DependSuffix) -MM Statistics.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Statistics.cpp$(PreprocessSuffix): Statistics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Statistics.cpp$(PreprocessSuffix) Statistics.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Layer.cpp$(ObjectSuffix): Layer.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Layer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Layer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Layer.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Layer.cpp$(DependSuffix): Layer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Layer.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Layer.cpp$(DependSuffix) -MM Layer.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Layer.cpp$(PreprocessSuffix): Layer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Layer.cpp$(PreprocessSuffix) Layer.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Function.cpp$(ObjectSuffix): Function.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Function.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Function.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Function.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Function.cpp$(DependSuffix): Function.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Function.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Function.cpp$(DependSuffix) -MM Function.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Function.cpp$(PreprocessSuffix): Function.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Function.cpp$(PreprocessSuffix) Function.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Matrix.cpp$(ObjectSuffix): Matrix.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Matrix.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Matrix.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Matrix.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Matrix.cpp$(DependSuffix): Matrix.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Matrix.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Matrix.cpp$(DependSuffix) -MM Matrix.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Matrix.cpp$(PreprocessSuffix): Matrix.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Matrix.cpp$(PreprocessSuffix) Matrix.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TestChromo.cpp$(ObjectSuffix): TestChromo.cpp ../build-$(ConfigurationName)/SmartSweepersV2/TestChromo.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/TestChromo.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestChromo.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/TestChromo.cpp$(DependSuffix): TestChromo.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/TestChromo.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/TestChromo.cpp$(DependSuffix) -MM TestChromo.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TestChromo.cpp$(PreprocessSuffix): TestChromo.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/TestChromo.cpp$(PreprocessSuffix) TestChromo.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Tournament.cpp$(ObjectSuffix): Tournament.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Tournament.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Tournament.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Tournament.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Tournament.cpp$(DependSuffix): Tournament.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Tournament.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Tournament.cpp$(DependSuffix) -MM Tournament.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Tournament.cpp$(PreprocessSuffix): Tournament.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Tournament.cpp$(PreprocessSuffix) Tournament.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Mine.cpp$(ObjectSuffix): Mine.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Mine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Mine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Mine.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Mine.cpp$(DependSuffix): Mine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Mine.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Mine.cpp$(DependSuffix) -MM Mine.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Mine.cpp$(PreprocessSuffix): Mine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Mine.cpp$(PreprocessSuffix) Mine.cpp

../build-$(ConfigurationName)/SmartSweepersV2/SmartMineSweeper.cpp$(ObjectSuffix): SmartMineSweeper.cpp ../build-$(ConfigurationName)/SmartSweepersV2/SmartMineSweeper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/SmartMineSweeper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SmartMineSweeper.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/SmartMineSweeper.cpp$(DependSuffix): SmartMineSweeper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/SmartMineSweeper.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/SmartMineSweeper.cpp$(DependSuffix) -MM SmartMineSweeper.cpp

../build-$(ConfigurationName)/SmartSweepersV2/SmartMineSweeper.cpp$(PreprocessSuffix): SmartMineSweeper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/SmartMineSweeper.cpp$(PreprocessSuffix) SmartMineSweeper.cpp

../build-$(ConfigurationName)/SmartSweepersV2/RGBColor.cpp$(ObjectSuffix): RGBColor.cpp ../build-$(ConfigurationName)/SmartSweepersV2/RGBColor.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/RGBColor.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RGBColor.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/RGBColor.cpp$(DependSuffix): RGBColor.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/RGBColor.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/RGBColor.cpp$(DependSuffix) -MM RGBColor.cpp

../build-$(ConfigurationName)/SmartSweepersV2/RGBColor.cpp$(PreprocessSuffix): RGBColor.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/RGBColor.cpp$(PreprocessSuffix) RGBColor.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Plane.cpp$(ObjectSuffix): Plane.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Plane.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Plane.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Plane.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Plane.cpp$(DependSuffix): Plane.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Plane.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Plane.cpp$(DependSuffix) -MM Plane.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Plane.cpp$(PreprocessSuffix): Plane.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Plane.cpp$(PreprocessSuffix) Plane.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Reserve.cpp$(ObjectSuffix): Reserve.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Reserve.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Reserve.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Reserve.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Reserve.cpp$(DependSuffix): Reserve.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Reserve.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Reserve.cpp$(DependSuffix) -MM Reserve.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Reserve.cpp$(PreprocessSuffix): Reserve.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Reserve.cpp$(PreprocessSuffix) Reserve.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Matrix2D.cpp$(ObjectSuffix): Matrix2D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Matrix2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Matrix2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Matrix2D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Matrix2D.cpp$(DependSuffix): Matrix2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Matrix2D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Matrix2D.cpp$(DependSuffix) -MM Matrix2D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Matrix2D.cpp$(PreprocessSuffix): Matrix2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Matrix2D.cpp$(PreprocessSuffix) Matrix2D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/World.cpp$(ObjectSuffix): World.cpp ../build-$(ConfigurationName)/SmartSweepersV2/World.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/World.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/World.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/World.cpp$(DependSuffix): World.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/World.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/World.cpp$(DependSuffix) -MM World.cpp

../build-$(ConfigurationName)/SmartSweepersV2/World.cpp$(PreprocessSuffix): World.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/World.cpp$(PreprocessSuffix) World.cpp

../build-$(ConfigurationName)/SmartSweepersV2/SphereTree.cpp$(ObjectSuffix): SphereTree.cpp ../build-$(ConfigurationName)/SmartSweepersV2/SphereTree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/SphereTree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/SphereTree.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/SphereTree.cpp$(DependSuffix): SphereTree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/SphereTree.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/SphereTree.cpp$(DependSuffix) -MM SphereTree.cpp

../build-$(ConfigurationName)/SmartSweepersV2/SphereTree.cpp$(PreprocessSuffix): SphereTree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/SphereTree.cpp$(PreprocessSuffix) SphereTree.cpp

../build-$(ConfigurationName)/SmartSweepersV2/NeuralNetwork.cpp$(ObjectSuffix): NeuralNetwork.cpp ../build-$(ConfigurationName)/SmartSweepersV2/NeuralNetwork.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/NeuralNetwork.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NeuralNetwork.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/NeuralNetwork.cpp$(DependSuffix): NeuralNetwork.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/NeuralNetwork.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/NeuralNetwork.cpp$(DependSuffix) -MM NeuralNetwork.cpp

../build-$(ConfigurationName)/SmartSweepersV2/NeuralNetwork.cpp$(PreprocessSuffix): NeuralNetwork.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/NeuralNetwork.cpp$(PreprocessSuffix) NeuralNetwork.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Tank.cpp$(ObjectSuffix): Tank.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Tank.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Tank.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Tank.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Tank.cpp$(DependSuffix): Tank.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Tank.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Tank.cpp$(DependSuffix) -MM Tank.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Tank.cpp$(PreprocessSuffix): Tank.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Tank.cpp$(PreprocessSuffix) Tank.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp$(ObjectSuffix): ComputeComponentsIntervalsAlongAxes.cpp ../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ComputeComponentsIntervalsAlongAxes.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp$(DependSuffix): ComputeComponentsIntervalsAlongAxes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp$(DependSuffix) -MM ComputeComponentsIntervalsAlongAxes.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp$(PreprocessSuffix): ComputeComponentsIntervalsAlongAxes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxes.cpp$(PreprocessSuffix) ComputeComponentsIntervalsAlongAxes.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Solver.cpp$(ObjectSuffix): Solver.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Solver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Solver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Solver.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Solver.cpp$(DependSuffix): Solver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Solver.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Solver.cpp$(DependSuffix) -MM Solver.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Solver.cpp$(PreprocessSuffix): Solver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Solver.cpp$(PreprocessSuffix) Solver.cpp

../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrMine.cpp$(ObjectSuffix): IsSharedPtrMine.cpp ../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrMine.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/IsSharedPtrMine.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IsSharedPtrMine.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrMine.cpp$(DependSuffix): IsSharedPtrMine.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrMine.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrMine.cpp$(DependSuffix) -MM IsSharedPtrMine.cpp

../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrMine.cpp$(PreprocessSuffix): IsSharedPtrMine.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrMine.cpp$(PreprocessSuffix) IsSharedPtrMine.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Graphics.cpp$(ObjectSuffix): Graphics.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Graphics.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Graphics.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Graphics.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Graphics.cpp$(DependSuffix): Graphics.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Graphics.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Graphics.cpp$(DependSuffix) -MM Graphics.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Graphics.cpp$(PreprocessSuffix): Graphics.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Graphics.cpp$(PreprocessSuffix) Graphics.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Vector.cpp$(ObjectSuffix): Vector.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Vector.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Vector.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Vector.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Vector.cpp$(DependSuffix): Vector.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Vector.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Vector.cpp$(DependSuffix) -MM Vector.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Vector.cpp$(PreprocessSuffix): Vector.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Vector.cpp$(PreprocessSuffix) Vector.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Camera.cpp$(ObjectSuffix): Camera.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Camera.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Camera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Camera.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Camera.cpp$(DependSuffix): Camera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Camera.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Camera.cpp$(DependSuffix) -MM Camera.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Camera.cpp$(PreprocessSuffix): Camera.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Camera.cpp$(PreprocessSuffix) Camera.cpp

../build-$(ConfigurationName)/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp$(ObjectSuffix): RandomGeneratorOfSweepersAndMines.cpp ../build-$(ConfigurationName)/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/RandomGeneratorOfSweepersAndMines.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp$(DependSuffix): RandomGeneratorOfSweepersAndMines.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp$(DependSuffix) -MM RandomGeneratorOfSweepersAndMines.cpp

../build-$(ConfigurationName)/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp$(PreprocessSuffix): RandomGeneratorOfSweepersAndMines.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/RandomGeneratorOfSweepersAndMines.cpp$(PreprocessSuffix) RandomGeneratorOfSweepersAndMines.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Vector3D.cpp$(ObjectSuffix): Vector3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Vector3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Vector3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Vector3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Vector3D.cpp$(DependSuffix): Vector3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Vector3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Vector3D.cpp$(DependSuffix) -MM Vector3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Vector3D.cpp$(PreprocessSuffix): Vector3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Vector3D.cpp$(PreprocessSuffix) Vector3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Mean.cpp$(ObjectSuffix): Mean.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Mean.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Mean.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Mean.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Mean.cpp$(DependSuffix): Mean.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Mean.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Mean.cpp$(DependSuffix) -MM Mean.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Mean.cpp$(PreprocessSuffix): Mean.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Mean.cpp$(PreprocessSuffix) Mean.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Intersectable.cpp$(ObjectSuffix): Intersectable.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Intersectable.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Intersectable.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Intersectable.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Intersectable.cpp$(DependSuffix): Intersectable.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Intersectable.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Intersectable.cpp$(DependSuffix) -MM Intersectable.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Intersectable.cpp$(PreprocessSuffix): Intersectable.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Intersectable.cpp$(PreprocessSuffix) Intersectable.cpp

../build-$(ConfigurationName)/SmartSweepersV2/IsMovableNonMovablePair.cpp$(ObjectSuffix): IsMovableNonMovablePair.cpp ../build-$(ConfigurationName)/SmartSweepersV2/IsMovableNonMovablePair.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/IsMovableNonMovablePair.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IsMovableNonMovablePair.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/IsMovableNonMovablePair.cpp$(DependSuffix): IsMovableNonMovablePair.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/IsMovableNonMovablePair.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/IsMovableNonMovablePair.cpp$(DependSuffix) -MM IsMovableNonMovablePair.cpp

../build-$(ConfigurationName)/SmartSweepersV2/IsMovableNonMovablePair.cpp$(PreprocessSuffix): IsMovableNonMovablePair.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/IsMovableNonMovablePair.cpp$(PreprocessSuffix) IsMovableNonMovablePair.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TestCamera.cpp$(ObjectSuffix): TestCamera.cpp ../build-$(ConfigurationName)/SmartSweepersV2/TestCamera.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/TestCamera.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestCamera.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/TestCamera.cpp$(DependSuffix): TestCamera.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/TestCamera.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/TestCamera.cpp$(DependSuffix) -MM TestCamera.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TestCamera.cpp$(PreprocessSuffix): TestCamera.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/TestCamera.cpp$(PreprocessSuffix) TestCamera.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Vector2D.cpp$(ObjectSuffix): Vector2D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Vector2D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Vector2D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Vector2D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Vector2D.cpp$(DependSuffix): Vector2D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Vector2D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Vector2D.cpp$(DependSuffix) -MM Vector2D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Vector2D.cpp$(PreprocessSuffix): Vector2D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Vector2D.cpp$(PreprocessSuffix) Vector2D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Partition_Triangles.cpp$(ObjectSuffix): Partition_Triangles.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Partition_Triangles.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Partition_Triangles.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Partition_Triangles.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Partition_Triangles.cpp$(DependSuffix): Partition_Triangles.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Partition_Triangles.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Partition_Triangles.cpp$(DependSuffix) -MM Partition_Triangles.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Partition_Triangles.cpp$(PreprocessSuffix): Partition_Triangles.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Partition_Triangles.cpp$(PreprocessSuffix) Partition_Triangles.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Polygon.cpp$(ObjectSuffix): Polygon.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Polygon.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Polygon.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Polygon.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Polygon.cpp$(DependSuffix): Polygon.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Polygon.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Polygon.cpp$(DependSuffix) -MM Polygon.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Polygon.cpp$(PreprocessSuffix): Polygon.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Polygon.cpp$(PreprocessSuffix) Polygon.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesCenters.cpp$(ObjectSuffix): ComputeTrianglesCenters.cpp ../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesCenters.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/ComputeTrianglesCenters.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ComputeTrianglesCenters.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesCenters.cpp$(DependSuffix): ComputeTrianglesCenters.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesCenters.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesCenters.cpp$(DependSuffix) -MM ComputeTrianglesCenters.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesCenters.cpp$(PreprocessSuffix): ComputeTrianglesCenters.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesCenters.cpp$(PreprocessSuffix) ComputeTrianglesCenters.cpp

../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp$(ObjectSuffix): IsSharedPtrSmartMineSweeper.cpp ../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IsSharedPtrSmartMineSweeper.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp$(DependSuffix): IsSharedPtrSmartMineSweeper.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp$(DependSuffix) -MM IsSharedPtrSmartMineSweeper.cpp

../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp$(PreprocessSuffix): IsSharedPtrSmartMineSweeper.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrSmartMineSweeper.cpp$(PreprocessSuffix) IsSharedPtrSmartMineSweeper.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DefaultBrainEvolver.cpp$(ObjectSuffix): DefaultBrainEvolver.cpp ../build-$(ConfigurationName)/SmartSweepersV2/DefaultBrainEvolver.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/DefaultBrainEvolver.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DefaultBrainEvolver.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/DefaultBrainEvolver.cpp$(DependSuffix): DefaultBrainEvolver.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/DefaultBrainEvolver.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/DefaultBrainEvolver.cpp$(DependSuffix) -MM DefaultBrainEvolver.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DefaultBrainEvolver.cpp$(PreprocessSuffix): DefaultBrainEvolver.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/DefaultBrainEvolver.cpp$(PreprocessSuffix) DefaultBrainEvolver.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Settings.cpp$(ObjectSuffix): Settings.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Settings.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Settings.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Settings.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Settings.cpp$(DependSuffix): Settings.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Settings.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Settings.cpp$(DependSuffix) -MM Settings.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Settings.cpp$(PreprocessSuffix): Settings.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Settings.cpp$(PreprocessSuffix) Settings.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Triangle.cpp$(ObjectSuffix): Triangle.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Triangle.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Triangle.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Triangle.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Triangle.cpp$(DependSuffix): Triangle.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Triangle.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Triangle.cpp$(DependSuffix) -MM Triangle.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Triangle.cpp$(PreprocessSuffix): Triangle.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Triangle.cpp$(PreprocessSuffix) Triangle.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DynamicSphere.cpp$(ObjectSuffix): DynamicSphere.cpp ../build-$(ConfigurationName)/SmartSweepersV2/DynamicSphere.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/DynamicSphere.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DynamicSphere.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/DynamicSphere.cpp$(DependSuffix): DynamicSphere.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/DynamicSphere.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/DynamicSphere.cpp$(DependSuffix) -MM DynamicSphere.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DynamicSphere.cpp$(PreprocessSuffix): DynamicSphere.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/DynamicSphere.cpp$(PreprocessSuffix) DynamicSphere.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Covariance.cpp$(ObjectSuffix): Covariance.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Covariance.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Covariance.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Covariance.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Covariance.cpp$(DependSuffix): Covariance.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Covariance.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Covariance.cpp$(DependSuffix) -MM Covariance.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Covariance.cpp$(PreprocessSuffix): Covariance.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Covariance.cpp$(PreprocessSuffix) Covariance.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Simulation.cpp$(ObjectSuffix): Simulation.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Simulation.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Simulation.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Simulation.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Simulation.cpp$(DependSuffix): Simulation.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Simulation.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Simulation.cpp$(DependSuffix) -MM Simulation.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Simulation.cpp$(PreprocessSuffix): Simulation.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Simulation.cpp$(PreprocessSuffix) Simulation.cpp

../build-$(ConfigurationName)/SmartSweepersV2/MTLLoader.cpp$(ObjectSuffix): MTLLoader.cpp ../build-$(ConfigurationName)/SmartSweepersV2/MTLLoader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/MTLLoader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MTLLoader.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/MTLLoader.cpp$(DependSuffix): MTLLoader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/MTLLoader.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/MTLLoader.cpp$(DependSuffix) -MM MTLLoader.cpp

../build-$(ConfigurationName)/SmartSweepersV2/MTLLoader.cpp$(PreprocessSuffix): MTLLoader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/MTLLoader.cpp$(PreprocessSuffix) MTLLoader.cpp

../build-$(ConfigurationName)/SmartSweepersV2/MeshBuilder.cpp$(ObjectSuffix): MeshBuilder.cpp ../build-$(ConfigurationName)/SmartSweepersV2/MeshBuilder.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/MeshBuilder.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MeshBuilder.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/MeshBuilder.cpp$(DependSuffix): MeshBuilder.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/MeshBuilder.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/MeshBuilder.cpp$(DependSuffix) -MM MeshBuilder.cpp

../build-$(ConfigurationName)/SmartSweepersV2/MeshBuilder.cpp$(PreprocessSuffix): MeshBuilder.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/MeshBuilder.cpp$(PreprocessSuffix) MeshBuilder.cpp

../build-$(ConfigurationName)/SmartSweepersV2/GaussPointsFit.cpp$(ObjectSuffix): GaussPointsFit.cpp ../build-$(ConfigurationName)/SmartSweepersV2/GaussPointsFit.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/GaussPointsFit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GaussPointsFit.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/GaussPointsFit.cpp$(DependSuffix): GaussPointsFit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/GaussPointsFit.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/GaussPointsFit.cpp$(DependSuffix) -MM GaussPointsFit.cpp

../build-$(ConfigurationName)/SmartSweepersV2/GaussPointsFit.cpp$(PreprocessSuffix): GaussPointsFit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/GaussPointsFit.cpp$(PreprocessSuffix) GaussPointsFit.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Grid3D.cpp$(ObjectSuffix): Grid3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Grid3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Grid3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Grid3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Grid3D.cpp$(DependSuffix): Grid3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Grid3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Grid3D.cpp$(DependSuffix) -MM Grid3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Grid3D.cpp$(PreprocessSuffix): Grid3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Grid3D.cpp$(PreprocessSuffix) Grid3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TestWorldMesh.cpp$(ObjectSuffix): TestWorldMesh.cpp ../build-$(ConfigurationName)/SmartSweepersV2/TestWorldMesh.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/TestWorldMesh.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestWorldMesh.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/TestWorldMesh.cpp$(DependSuffix): TestWorldMesh.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/TestWorldMesh.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/TestWorldMesh.cpp$(DependSuffix) -MM TestWorldMesh.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TestWorldMesh.cpp$(PreprocessSuffix): TestWorldMesh.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/TestWorldMesh.cpp$(PreprocessSuffix) TestWorldMesh.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesAreas.cpp$(ObjectSuffix): ComputeTrianglesAreas.cpp ../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesAreas.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/ComputeTrianglesAreas.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ComputeTrianglesAreas.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesAreas.cpp$(DependSuffix): ComputeTrianglesAreas.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesAreas.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesAreas.cpp$(DependSuffix) -MM ComputeTrianglesAreas.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesAreas.cpp$(PreprocessSuffix): ComputeTrianglesAreas.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeTrianglesAreas.cpp$(PreprocessSuffix) ComputeTrianglesAreas.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Mobile.cpp$(ObjectSuffix): Mobile.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Mobile.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Mobile.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Mobile.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Mobile.cpp$(DependSuffix): Mobile.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Mobile.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Mobile.cpp$(DependSuffix) -MM Mobile.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Mobile.cpp$(PreprocessSuffix): Mobile.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Mobile.cpp$(PreprocessSuffix) Mobile.cpp

../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp$(ObjectSuffix): IsSharedPtrPhysicObject3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/IsSharedPtrPhysicObject3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp$(DependSuffix): IsSharedPtrPhysicObject3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp$(DependSuffix) -MM IsSharedPtrPhysicObject3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp$(PreprocessSuffix): IsSharedPtrPhysicObject3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/IsSharedPtrPhysicObject3D.cpp$(PreprocessSuffix) IsSharedPtrPhysicObject3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Sensors.cpp$(ObjectSuffix): Sensors.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Sensors.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Sensors.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Sensors.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Sensors.cpp$(DependSuffix): Sensors.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Sensors.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Sensors.cpp$(DependSuffix) -MM Sensors.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Sensors.cpp$(PreprocessSuffix): Sensors.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Sensors.cpp$(PreprocessSuffix) Sensors.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DynamicPlane.cpp$(ObjectSuffix): DynamicPlane.cpp ../build-$(ConfigurationName)/SmartSweepersV2/DynamicPlane.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/DynamicPlane.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DynamicPlane.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/DynamicPlane.cpp$(DependSuffix): DynamicPlane.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/DynamicPlane.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/DynamicPlane.cpp$(DependSuffix) -MM DynamicPlane.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DynamicPlane.cpp$(PreprocessSuffix): DynamicPlane.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/DynamicPlane.cpp$(PreprocessSuffix) DynamicPlane.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DefaultSteeringFunction.cpp$(ObjectSuffix): DefaultSteeringFunction.cpp ../build-$(ConfigurationName)/SmartSweepersV2/DefaultSteeringFunction.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/DefaultSteeringFunction.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/DefaultSteeringFunction.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/DefaultSteeringFunction.cpp$(DependSuffix): DefaultSteeringFunction.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/DefaultSteeringFunction.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/DefaultSteeringFunction.cpp$(DependSuffix) -MM DefaultSteeringFunction.cpp

../build-$(ConfigurationName)/SmartSweepersV2/DefaultSteeringFunction.cpp$(PreprocessSuffix): DefaultSteeringFunction.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/DefaultSteeringFunction.cpp$(PreprocessSuffix) DefaultSteeringFunction.cpp

../build-$(ConfigurationName)/SmartSweepersV2/CompareMyChromosome.cpp$(ObjectSuffix): CompareMyChromosome.cpp ../build-$(ConfigurationName)/SmartSweepersV2/CompareMyChromosome.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/CompareMyChromosome.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/CompareMyChromosome.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/CompareMyChromosome.cpp$(DependSuffix): CompareMyChromosome.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/CompareMyChromosome.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/CompareMyChromosome.cpp$(DependSuffix) -MM CompareMyChromosome.cpp

../build-$(ConfigurationName)/SmartSweepersV2/CompareMyChromosome.cpp$(PreprocessSuffix): CompareMyChromosome.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/CompareMyChromosome.cpp$(PreprocessSuffix) CompareMyChromosome.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Line.cpp$(ObjectSuffix): Line.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Line.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Line.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Line.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Line.cpp$(DependSuffix): Line.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Line.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Line.cpp$(DependSuffix) -MM Line.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Line.cpp$(PreprocessSuffix): Line.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Line.cpp$(PreprocessSuffix) Line.cpp

../build-$(ConfigurationName)/SmartSweepersV2/BoundingVolumeBuilder3D.cpp$(ObjectSuffix): BoundingVolumeBuilder3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/BoundingVolumeBuilder3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/BoundingVolumeBuilder3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/BoundingVolumeBuilder3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/BoundingVolumeBuilder3D.cpp$(DependSuffix): BoundingVolumeBuilder3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/BoundingVolumeBuilder3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/BoundingVolumeBuilder3D.cpp$(DependSuffix) -MM BoundingVolumeBuilder3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/BoundingVolumeBuilder3D.cpp$(PreprocessSuffix): BoundingVolumeBuilder3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/BoundingVolumeBuilder3D.cpp$(PreprocessSuffix) BoundingVolumeBuilder3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/NotClosestObjectException.cpp$(ObjectSuffix): NotClosestObjectException.cpp ../build-$(ConfigurationName)/SmartSweepersV2/NotClosestObjectException.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/NotClosestObjectException.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/NotClosestObjectException.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/NotClosestObjectException.cpp$(DependSuffix): NotClosestObjectException.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/NotClosestObjectException.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/NotClosestObjectException.cpp$(DependSuffix) -MM NotClosestObjectException.cpp

../build-$(ConfigurationName)/SmartSweepersV2/NotClosestObjectException.cpp$(PreprocessSuffix): NotClosestObjectException.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/NotClosestObjectException.cpp$(PreprocessSuffix) NotClosestObjectException.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp$(ObjectSuffix): ComputeComponentsIntervalsAlongAxis.cpp ../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ComputeComponentsIntervalsAlongAxis.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp$(DependSuffix): ComputeComponentsIntervalsAlongAxis.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp$(DependSuffix) -MM ComputeComponentsIntervalsAlongAxis.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp$(PreprocessSuffix): ComputeComponentsIntervalsAlongAxis.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeComponentsIntervalsAlongAxis.cpp$(PreprocessSuffix) ComputeComponentsIntervalsAlongAxis.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Octree.cpp$(ObjectSuffix): Octree.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Octree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Octree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Octree.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Octree.cpp$(DependSuffix): Octree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Octree.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Octree.cpp$(DependSuffix) -MM Octree.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Octree.cpp$(PreprocessSuffix): Octree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Octree.cpp$(PreprocessSuffix) Octree.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Quaternion.cpp$(ObjectSuffix): Quaternion.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Quaternion.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Quaternion.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Quaternion.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Quaternion.cpp$(DependSuffix): Quaternion.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Quaternion.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Quaternion.cpp$(DependSuffix) -MM Quaternion.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Quaternion.cpp$(PreprocessSuffix): Quaternion.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Quaternion.cpp$(PreprocessSuffix) Quaternion.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Indexes.cpp$(ObjectSuffix): Indexes.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Indexes.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Indexes.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Indexes.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Indexes.cpp$(DependSuffix): Indexes.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Indexes.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Indexes.cpp$(DependSuffix) -MM Indexes.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Indexes.cpp$(PreprocessSuffix): Indexes.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Indexes.cpp$(PreprocessSuffix) Indexes.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Quad.cpp$(ObjectSuffix): Quad.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Quad.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Quad.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Quad.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Quad.cpp$(DependSuffix): Quad.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Quad.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Quad.cpp$(DependSuffix) -MM Quad.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Quad.cpp$(PreprocessSuffix): Quad.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Quad.cpp$(PreprocessSuffix) Quad.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TestIcosahedron.cpp$(ObjectSuffix): TestIcosahedron.cpp ../build-$(ConfigurationName)/SmartSweepersV2/TestIcosahedron.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/TestIcosahedron.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TestIcosahedron.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/TestIcosahedron.cpp$(DependSuffix): TestIcosahedron.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/TestIcosahedron.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/TestIcosahedron.cpp$(DependSuffix) -MM TestIcosahedron.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TestIcosahedron.cpp$(PreprocessSuffix): TestIcosahedron.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/TestIcosahedron.cpp$(PreprocessSuffix) TestIcosahedron.cpp

../build-$(ConfigurationName)/SmartSweepersV2/VTN.cpp$(ObjectSuffix): VTN.cpp ../build-$(ConfigurationName)/SmartSweepersV2/VTN.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/VTN.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/VTN.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/VTN.cpp$(DependSuffix): VTN.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/VTN.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/VTN.cpp$(DependSuffix) -MM VTN.cpp

../build-$(ConfigurationName)/SmartSweepersV2/VTN.cpp$(PreprocessSuffix): VTN.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/VTN.cpp$(PreprocessSuffix) VTN.cpp

../build-$(ConfigurationName)/SmartSweepersV2/MaterialManager.cpp$(ObjectSuffix): MaterialManager.cpp ../build-$(ConfigurationName)/SmartSweepersV2/MaterialManager.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/MaterialManager.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/MaterialManager.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/MaterialManager.cpp$(DependSuffix): MaterialManager.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/MaterialManager.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/MaterialManager.cpp$(DependSuffix) -MM MaterialManager.cpp

../build-$(ConfigurationName)/SmartSweepersV2/MaterialManager.cpp$(PreprocessSuffix): MaterialManager.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/MaterialManager.cpp$(PreprocessSuffix) MaterialManager.cpp

../build-$(ConfigurationName)/SmartSweepersV2/LineSegment.cpp$(ObjectSuffix): LineSegment.cpp ../build-$(ConfigurationName)/SmartSweepersV2/LineSegment.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/LineSegment.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/LineSegment.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/LineSegment.cpp$(DependSuffix): LineSegment.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/LineSegment.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/LineSegment.cpp$(DependSuffix) -MM LineSegment.cpp

../build-$(ConfigurationName)/SmartSweepersV2/LineSegment.cpp$(PreprocessSuffix): LineSegment.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/LineSegment.cpp$(PreprocessSuffix) LineSegment.cpp

../build-$(ConfigurationName)/SmartSweepersV2/GaussTrianglesFit.cpp$(ObjectSuffix): GaussTrianglesFit.cpp ../build-$(ConfigurationName)/SmartSweepersV2/GaussTrianglesFit.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/GaussTrianglesFit.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GaussTrianglesFit.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/GaussTrianglesFit.cpp$(DependSuffix): GaussTrianglesFit.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/GaussTrianglesFit.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/GaussTrianglesFit.cpp$(DependSuffix) -MM GaussTrianglesFit.cpp

../build-$(ConfigurationName)/SmartSweepersV2/GaussTrianglesFit.cpp$(PreprocessSuffix): GaussTrianglesFit.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/GaussTrianglesFit.cpp$(PreprocessSuffix) GaussTrianglesFit.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Face.cpp$(ObjectSuffix): Face.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Face.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Face.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Face.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Face.cpp$(DependSuffix): Face.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Face.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Face.cpp$(DependSuffix) -MM Face.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Face.cpp$(PreprocessSuffix): Face.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Face.cpp$(PreprocessSuffix) Face.cpp

../build-$(ConfigurationName)/SmartSweepersV2/OBJ_Loader.cpp$(ObjectSuffix): OBJ_Loader.cpp ../build-$(ConfigurationName)/SmartSweepersV2/OBJ_Loader.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/OBJ_Loader.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OBJ_Loader.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/OBJ_Loader.cpp$(DependSuffix): OBJ_Loader.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/OBJ_Loader.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/OBJ_Loader.cpp$(DependSuffix) -MM OBJ_Loader.cpp

../build-$(ConfigurationName)/SmartSweepersV2/OBJ_Loader.cpp$(PreprocessSuffix): OBJ_Loader.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/OBJ_Loader.cpp$(PreprocessSuffix) OBJ_Loader.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Gudermann.cpp$(ObjectSuffix): Gudermann.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Gudermann.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Gudermann.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Gudermann.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Gudermann.cpp$(DependSuffix): Gudermann.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Gudermann.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Gudermann.cpp$(DependSuffix) -MM Gudermann.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Gudermann.cpp$(PreprocessSuffix): Gudermann.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Gudermann.cpp$(PreprocessSuffix) Gudermann.cpp

../build-$(ConfigurationName)/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp$(ObjectSuffix): AreBothSharedPtrMovablePhysicObject3D.cpp ../build-$(ConfigurationName)/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/AreBothSharedPtrMovablePhysicObject3D.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp$(DependSuffix): AreBothSharedPtrMovablePhysicObject3D.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp$(DependSuffix) -MM AreBothSharedPtrMovablePhysicObject3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp$(PreprocessSuffix): AreBothSharedPtrMovablePhysicObject3D.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/AreBothSharedPtrMovablePhysicObject3D.cpp$(PreprocessSuffix) AreBothSharedPtrMovablePhysicObject3D.cpp

../build-$(ConfigurationName)/SmartSweepersV2/UnsupportedOperationException.cpp$(ObjectSuffix): UnsupportedOperationException.cpp ../build-$(ConfigurationName)/SmartSweepersV2/UnsupportedOperationException.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/UnsupportedOperationException.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UnsupportedOperationException.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/UnsupportedOperationException.cpp$(DependSuffix): UnsupportedOperationException.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/UnsupportedOperationException.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/UnsupportedOperationException.cpp$(DependSuffix) -MM UnsupportedOperationException.cpp

../build-$(ConfigurationName)/SmartSweepersV2/UnsupportedOperationException.cpp$(PreprocessSuffix): UnsupportedOperationException.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/UnsupportedOperationException.cpp$(PreprocessSuffix) UnsupportedOperationException.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeVertexList.cpp$(ObjectSuffix): ComputeVertexList.cpp ../build-$(ConfigurationName)/SmartSweepersV2/ComputeVertexList.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/ComputeVertexList.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ComputeVertexList.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/ComputeVertexList.cpp$(DependSuffix): ComputeVertexList.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/ComputeVertexList.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/ComputeVertexList.cpp$(DependSuffix) -MM ComputeVertexList.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ComputeVertexList.cpp$(PreprocessSuffix): ComputeVertexList.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/ComputeVertexList.cpp$(PreprocessSuffix) ComputeVertexList.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Rand.cpp$(ObjectSuffix): Rand.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Rand.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Rand.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Rand.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Rand.cpp$(DependSuffix): Rand.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Rand.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Rand.cpp$(DependSuffix) -MM Rand.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Rand.cpp$(PreprocessSuffix): Rand.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Rand.cpp$(PreprocessSuffix) Rand.cpp

../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3DTree.cpp$(ObjectSuffix): OrientedBox3DTree.cpp ../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3DTree.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/OrientedBox3DTree.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OrientedBox3DTree.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3DTree.cpp$(DependSuffix): OrientedBox3DTree.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3DTree.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3DTree.cpp$(DependSuffix) -MM OrientedBox3DTree.cpp

../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3DTree.cpp$(PreprocessSuffix): OrientedBox3DTree.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/OrientedBox3DTree.cpp$(PreprocessSuffix) OrientedBox3DTree.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Utility.cpp$(ObjectSuffix): Utility.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Utility.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Utility.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Utility.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Utility.cpp$(DependSuffix): Utility.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Utility.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Utility.cpp$(DependSuffix) -MM Utility.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Utility.cpp$(PreprocessSuffix): Utility.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Utility.cpp$(PreprocessSuffix) Utility.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Intersection.cpp$(ObjectSuffix): Intersection.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Intersection.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Intersection.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Intersection.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Intersection.cpp$(DependSuffix): Intersection.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Intersection.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Intersection.cpp$(DependSuffix) -MM Intersection.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Intersection.cpp$(PreprocessSuffix): Intersection.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Intersection.cpp$(PreprocessSuffix) Intersection.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TridiagonalForm.cpp$(ObjectSuffix): TridiagonalForm.cpp ../build-$(ConfigurationName)/SmartSweepersV2/TridiagonalForm.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/TridiagonalForm.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/TridiagonalForm.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/TridiagonalForm.cpp$(DependSuffix): TridiagonalForm.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/TridiagonalForm.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/TridiagonalForm.cpp$(DependSuffix) -MM TridiagonalForm.cpp

../build-$(ConfigurationName)/SmartSweepersV2/TridiagonalForm.cpp$(PreprocessSuffix): TridiagonalForm.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/TridiagonalForm.cpp$(PreprocessSuffix) TridiagonalForm.cpp

../build-$(ConfigurationName)/SmartSweepersV2/order_eigen_values.cpp$(ObjectSuffix): order_eigen_values.cpp ../build-$(ConfigurationName)/SmartSweepersV2/order_eigen_values.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/order_eigen_values.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/order_eigen_values.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/order_eigen_values.cpp$(DependSuffix): order_eigen_values.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/order_eigen_values.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/order_eigen_values.cpp$(DependSuffix) -MM order_eigen_values.cpp

../build-$(ConfigurationName)/SmartSweepersV2/order_eigen_values.cpp$(PreprocessSuffix): order_eigen_values.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/order_eigen_values.cpp$(PreprocessSuffix) order_eigen_values.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Support.cpp$(ObjectSuffix): Support.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Support.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Support.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Support.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Support.cpp$(DependSuffix): Support.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Support.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Support.cpp$(DependSuffix) -MM Support.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Support.cpp$(PreprocessSuffix): Support.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Support.cpp$(PreprocessSuffix) Support.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Box.cpp$(ObjectSuffix): Box.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Box.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Box.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Box.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Box.cpp$(DependSuffix): Box.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Box.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Box.cpp$(DependSuffix) -MM Box.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Box.cpp$(PreprocessSuffix): Box.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Box.cpp$(PreprocessSuffix) Box.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Brain.cpp$(ObjectSuffix): Brain.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Brain.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Brain.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Brain.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Brain.cpp$(DependSuffix): Brain.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Brain.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Brain.cpp$(DependSuffix) -MM Brain.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Brain.cpp$(PreprocessSuffix): Brain.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Brain.cpp$(PreprocessSuffix) Brain.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Eigen.cpp$(ObjectSuffix): Eigen.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Eigen.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Eigen.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Eigen.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Eigen.cpp$(DependSuffix): Eigen.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Eigen.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Eigen.cpp$(DependSuffix) -MM Eigen.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Eigen.cpp$(PreprocessSuffix): Eigen.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Eigen.cpp$(PreprocessSuffix) Eigen.cpp

../build-$(ConfigurationName)/SmartSweepersV2/GraphicObject.cpp$(ObjectSuffix): GraphicObject.cpp ../build-$(ConfigurationName)/SmartSweepersV2/GraphicObject.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/GraphicObject.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/GraphicObject.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/GraphicObject.cpp$(DependSuffix): GraphicObject.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/GraphicObject.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/GraphicObject.cpp$(DependSuffix) -MM GraphicObject.cpp

../build-$(ConfigurationName)/SmartSweepersV2/GraphicObject.cpp$(PreprocessSuffix): GraphicObject.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/GraphicObject.cpp$(PreprocessSuffix) GraphicObject.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Application.cpp$(ObjectSuffix): Application.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Application.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Application.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Application.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Application.cpp$(DependSuffix): Application.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Application.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Application.cpp$(DependSuffix) -MM Application.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Application.cpp$(PreprocessSuffix): Application.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Application.cpp$(PreprocessSuffix) Application.cpp

../build-$(ConfigurationName)/SmartSweepersV2/OrientedEllipsoid.cpp$(ObjectSuffix): OrientedEllipsoid.cpp ../build-$(ConfigurationName)/SmartSweepersV2/OrientedEllipsoid.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/OrientedEllipsoid.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/OrientedEllipsoid.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/OrientedEllipsoid.cpp$(DependSuffix): OrientedEllipsoid.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/OrientedEllipsoid.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/OrientedEllipsoid.cpp$(DependSuffix) -MM OrientedEllipsoid.cpp

../build-$(ConfigurationName)/SmartSweepersV2/OrientedEllipsoid.cpp$(PreprocessSuffix): OrientedEllipsoid.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/OrientedEllipsoid.cpp$(PreprocessSuffix) OrientedEllipsoid.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ModelIterator.cpp$(ObjectSuffix): ModelIterator.cpp ../build-$(ConfigurationName)/SmartSweepersV2/ModelIterator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/ModelIterator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ModelIterator.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/ModelIterator.cpp$(DependSuffix): ModelIterator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/ModelIterator.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/ModelIterator.cpp$(DependSuffix) -MM ModelIterator.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ModelIterator.cpp$(PreprocessSuffix): ModelIterator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/ModelIterator.cpp$(PreprocessSuffix) ModelIterator.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ModelConstantIterator.cpp$(ObjectSuffix): ModelConstantIterator.cpp ../build-$(ConfigurationName)/SmartSweepersV2/ModelConstantIterator.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/ModelConstantIterator.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/ModelConstantIterator.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/ModelConstantIterator.cpp$(DependSuffix): ModelConstantIterator.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/ModelConstantIterator.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/ModelConstantIterator.cpp$(DependSuffix) -MM ModelConstantIterator.cpp

../build-$(ConfigurationName)/SmartSweepersV2/ModelConstantIterator.cpp$(PreprocessSuffix): ModelConstantIterator.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/ModelConstantIterator.cpp$(PreprocessSuffix) ModelConstantIterator.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Model.cpp$(ObjectSuffix): Model.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Model.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Model.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Model.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Model.cpp$(DependSuffix): Model.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Model.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Model.cpp$(DependSuffix) -MM Model.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Model.cpp$(PreprocessSuffix): Model.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Model.cpp$(PreprocessSuffix) Model.cpp

../build-$(ConfigurationName)/SmartSweepersV2/main.cpp$(ObjectSuffix): main.cpp ../build-$(ConfigurationName)/SmartSweepersV2/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/main.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/main.cpp$(DependSuffix) -MM main.cpp

../build-$(ConfigurationName)/SmartSweepersV2/main.cpp$(PreprocessSuffix): main.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/main.cpp$(PreprocessSuffix) main.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Renderer.cpp$(ObjectSuffix): Renderer.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Renderer.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Renderer.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Renderer.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Renderer.cpp$(DependSuffix): Renderer.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Renderer.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Renderer.cpp$(DependSuffix) -MM Renderer.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Renderer.cpp$(PreprocessSuffix): Renderer.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Renderer.cpp$(PreprocessSuffix) Renderer.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Material.cpp$(ObjectSuffix): Material.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Material.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Material.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Material.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Material.cpp$(DependSuffix): Material.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Material.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Material.cpp$(DependSuffix) -MM Material.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Material.cpp$(PreprocessSuffix): Material.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Material.cpp$(PreprocessSuffix) Material.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Mesh.cpp$(ObjectSuffix): Mesh.cpp ../build-$(ConfigurationName)/SmartSweepersV2/Mesh.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/john/Documents/Programming/SmartSweepersV2/Mesh.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/Mesh.cpp$(ObjectSuffix) $(IncludePath)
../build-$(ConfigurationName)/SmartSweepersV2/Mesh.cpp$(DependSuffix): Mesh.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT../build-$(ConfigurationName)/SmartSweepersV2/Mesh.cpp$(ObjectSuffix) -MF../build-$(ConfigurationName)/SmartSweepersV2/Mesh.cpp$(DependSuffix) -MM Mesh.cpp

../build-$(ConfigurationName)/SmartSweepersV2/Mesh.cpp$(PreprocessSuffix): Mesh.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) ../build-$(ConfigurationName)/SmartSweepersV2/Mesh.cpp$(PreprocessSuffix) Mesh.cpp


-include ../build-$(ConfigurationName)/SmartSweepersV2//*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r $(IntermediateDirectory)


