#include "MySet.H"
#include "Tests.H"
#include <stdio.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

/*"struct elem" can correctly contain anything besides pointers*/



void UnitTests(void)
{
	set_tAdd__EmptySet();
	set_tAdd__IdenticalElem();
	set_tAdd__AnotherElem();
	set_tCheck__EmptySet();
	set_tCheck__NonEmptySet();
	set_tCheck__ExistingElem();
	set_tRemove__NonExistingElem();
	set_tRemove__ExistingElem();
	set_tIntersection__2EmptySets();
	set_tIntersection__1EmptySet();
	set_tIntersection__WithoutIntersection();
	set_tIntersection__WithIntersection();
	set_tUnion__2EmptySets();
	set_tUnion__1EmptySet();
	set_tUnion__WithoutIntersection();
	set_tUnion__WithIntersection();
}

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	UnitTests();

	return 0;
}
