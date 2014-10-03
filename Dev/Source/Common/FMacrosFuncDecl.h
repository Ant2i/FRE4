//#define DEFINE_METHOD_0(ReturnType, MethodName, ReturnStatement, NullImplementation) \
//	DEFINE_METHOD(ReturnType, MethodName, (), (), ReturnStatement, NullImplementation)
//	
//#define DEFINE_METHOD_1(ReturnType, MethodName, ParameterTypeA, ParameterNameA, ReturnStatement, NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA),(ParameterNameA),ReturnStatement,NullImplementation)
//	
//#define DEFINE_METHOD_2(ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ReturnStatement,NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA,ParameterTypeB ParameterNameB),(ParameterNameA,ParameterNameB),ReturnStatement,NullImplementation)
//	
//#define DEFINE_METHOD_3(ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ReturnStatement,NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA,ParameterTypeB ParameterNameB,ParameterTypeC ParameterNameC),(ParameterNameA,ParameterNameB,ParameterNameC),ReturnStatement,NullImplementation)
//	
//#define DEFINE_METHOD_4(ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ReturnStatement,NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA,ParameterTypeB ParameterNameB,ParameterTypeC ParameterNameC,ParameterTypeD ParameterNameD),(ParameterNameA,ParameterNameB,ParameterNameC,ParameterNameD),ReturnStatement,NullImplementation)
//	
//#define DEFINE_METHOD_5(ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ReturnStatement,NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA,ParameterTypeB ParameterNameB,ParameterTypeC ParameterNameC,ParameterTypeD ParameterNameD,ParameterTypeE ParameterNameE),(ParameterNameA,ParameterNameB,ParameterNameC,ParameterNameD,ParameterNameE),ReturnStatement,NullImplementation)
//	
//#define DEFINE_METHOD_6(ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ParameterTypeF,ParameterNameF,ReturnStatement,NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA,ParameterTypeB ParameterNameB,ParameterTypeC ParameterNameC,ParameterTypeD ParameterNameD,ParameterTypeE ParameterNameE,ParameterTypeF ParameterNameF),(ParameterNameA,ParameterNameB,ParameterNameC,ParameterNameD,ParameterNameE,ParameterNameF),ReturnStatement,NullImplementation)
//	
//#define DEFINE_METHOD_7(ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ParameterTypeF,ParameterNameF,ParameterTypeG,ParameterNameG,ReturnStatement,NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA,ParameterTypeB ParameterNameB,ParameterTypeC ParameterNameC,ParameterTypeD ParameterNameD,ParameterTypeE ParameterNameE,ParameterTypeF ParameterNameF,ParameterTypeG ParameterNameG),(ParameterNameA,ParameterNameB,ParameterNameC,ParameterNameD,ParameterNameE,ParameterNameF,ParameterNameG),ReturnStatement,NullImplementation)
//	
//#define DEFINE_METHOD_8(ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ParameterTypeF,ParameterNameF,ParameterTypeG,ParameterNameG,ParameterTypeH,ParameterNameH,ReturnStatement,NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA,ParameterTypeB ParameterNameB,ParameterTypeC ParameterNameC,ParameterTypeD ParameterNameD,ParameterTypeE ParameterNameE,ParameterTypeF ParameterNameF,ParameterTypeG ParameterNameG,ParameterTypeH ParameterNameH),(ParameterNameA,ParameterNameB,ParameterNameC,ParameterNameD,ParameterNameE,ParameterNameF,ParameterNameG,ParameterNameH),ReturnStatement,NullImplementation)
//
//#define DEFINE_METHOD_9(ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ParameterTypeF,ParameterNameF,ParameterTypeG,ParameterNameG,ParameterTypeH,ParameterNameH,ParameterTypeI,ParameterNameI,ReturnStatement,NullImplementation) \
//	DEFINE_METHOD(ReturnType,MethodName,(ParameterTypeA ParameterNameA,ParameterTypeB ParameterNameB,ParameterTypeC ParameterNameC,ParameterTypeD ParameterNameD,ParameterTypeE ParameterNameE,ParameterTypeF ParameterNameF,ParameterTypeG ParameterNameG,ParameterTypeH ParameterNameH,ParameterTypeI ParameterNameI),(ParameterNameA,ParameterNameB,ParameterNameC,ParameterNameD,ParameterNameE,ParameterNameF,ParameterNameG,ParameterNameH,ParameterNameI),ReturnStatement,NullImplementation)

////////////////////////
	
#define DEFINE_METHOD_0(DefMethod, ReturnType, MethodName, ReturnStatement, NullImplementation) \
	DefMethod(ReturnType, MethodName, (), (), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_1(DefMethod, ReturnType, MethodName, ParameterTypeA, ParameterNameA, ReturnStatement, NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA), (ParameterNameA), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_2(DefMethod, ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ReturnStatement,NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA, ParameterTypeB ParameterNameB), (ParameterNameA, ParameterNameB), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_3(DefMethod, ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ReturnStatement,NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA, ParameterTypeB ParameterNameB, ParameterTypeC ParameterNameC), (ParameterNameA, ParameterNameB, ParameterNameC), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_4(DefMethod, ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ReturnStatement,NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA, ParameterTypeB ParameterNameB, ParameterTypeC ParameterNameC, ParameterTypeD ParameterNameD), (ParameterNameA, ParameterNameB, ParameterNameC, ParameterNameD), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_5(DefMethod, ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ReturnStatement,NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA, ParameterTypeB ParameterNameB, ParameterTypeC ParameterNameC, ParameterTypeD ParameterNameD, ParameterTypeE ParameterNameE), (ParameterNameA, ParameterNameB, ParameterNameC, ParameterNameD, ParameterNameE), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_6(DefMethod, ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ParameterTypeF,ParameterNameF,ReturnStatement,NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA, ParameterTypeB ParameterNameB, ParameterTypeC ParameterNameC, ParameterTypeD ParameterNameD, ParameterTypeE ParameterNameE, ParameterTypeF ParameterNameF), (ParameterNameA, ParameterNameB, ParameterNameC, ParameterNameD, ParameterNameE, ParameterNameF), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_7(DefMethod, ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ParameterTypeF,ParameterNameF,ParameterTypeG,ParameterNameG,ReturnStatement,NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA, ParameterTypeB ParameterNameB, ParameterTypeC ParameterNameC, ParameterTypeD ParameterNameD, ParameterTypeE ParameterNameE, ParameterTypeF ParameterNameF, ParameterTypeG ParameterNameG), (ParameterNameA, ParameterNameB, ParameterNameC, ParameterNameD, ParameterNameE, ParameterNameF, ParameterNameG), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_8(DefMethod, ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ParameterTypeF,ParameterNameF,ParameterTypeG,ParameterNameG,ParameterTypeH,ParameterNameH,ReturnStatement,NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA, ParameterTypeB ParameterNameB, ParameterTypeC ParameterNameC, ParameterTypeD ParameterNameD, ParameterTypeE ParameterNameE, ParameterTypeF ParameterNameF, ParameterTypeG ParameterNameG, ParameterTypeH ParameterNameH), (ParameterNameA, ParameterNameB, ParameterNameC, ParameterNameD, ParameterNameE, ParameterNameF, ParameterNameG, ParameterNameH), ReturnStatement, NullImplementation)
	
#define DEFINE_METHOD_9(DefMethod, ReturnType,MethodName,ParameterTypeA,ParameterNameA,ParameterTypeB,ParameterNameB,ParameterTypeC,ParameterNameC,ParameterTypeD,ParameterNameD,ParameterTypeE,ParameterNameE,ParameterTypeF,ParameterNameF,ParameterTypeG,ParameterNameG,ParameterTypeH,ParameterNameH,ParameterTypeI,ParameterNameI,ReturnStatement,NullImplementation) \
	DefMethod(ReturnType, MethodName, (ParameterTypeA ParameterNameA, ParameterTypeB ParameterNameB, ParameterTypeC ParameterNameC, ParameterTypeD ParameterNameD, ParameterTypeE ParameterNameE, ParameterTypeF ParameterNameF, ParameterTypeG ParameterNameG, ParameterTypeH ParameterNameH, ParameterTypeI ParameterNameI), (ParameterNameA, ParameterNameB, ParameterNameC, ParameterNameD, ParameterNameE, ParameterNameF, ParameterNameG, ParameterNameH, ParameterNameI), ReturnStatement, NullImplementation)
