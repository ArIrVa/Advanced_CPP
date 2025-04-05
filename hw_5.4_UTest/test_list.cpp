#define CATCH_CONFIG_MAIN
#include"catch2/catch_all.hpp"
#include"list.h"

// Задача 1. Проверка базовых функций двусвзяного списка
	TEST_CASE("Empty") {
		List list;		
		SECTION("after the creation of the object") {
			CHECK(list.Empty() == true);
		}
		SECTION("not empty after adding an element") {
			list.PushBack(4);
			CHECK(list.Empty() == false);
		}
		SECTION("after clear") {
			list.Clear();			
			CHECK(list.Empty() == true);
		}
	}
	TEST_CASE("Size") {
		List list;		
		SECTION("after the creation of the object") {
			CHECK(list.Size() == 0);
		}
		SECTION("after adding elements") {
			list.PushBack(3);
			list.PushBack(0);
			CHECK(list.Size() == 2);
		}
		SECTION("after clear") {
			CHECK(list.Size() == 0);
		}
	}
	TEST_CASE("Clear") {
		List list;		
		list.PushBack(3);
		list.PushBack(0);				
		list.Clear();
		CHECK(list.Size() == 0);
	}

// Задача 2. Проверка функций добавления и получения элементов из двусвязного списка

	TEST_CASE("PushBack") {		
		SECTION("adding three elements") {
			List list;
			list.PushBack(3);
			list.PushBack(4);
			list.PushBack(5);
			CHECK(list.Size() == 3);
		}
	}
	TEST_CASE("PushFront") {		
		SECTION("adding two elements") {
			List list;
			list.PushFront(0);
			list.PushFront(2);
			CHECK(list.Size() == 2);
		}
	}
	TEST_CASE("PopBack") {		
		List list;
		SECTION("with empty list") {			
			CHECK_THROWS(list.PopBack());			
		}
		SECTION("with not empty list") {			
			list.PushFront(5);
			list.PushBack(4);
			CHECK_THROWS(list.PopBack());			
		}
	}
	TEST_CASE("PopFront") {
		List list;
		SECTION("with empty list") {
			list.PushBack(8);
			list.PushFront(6);
			list.PopFront();
			list.PopFront();
			CHECK_THROWS(list.PopFront());
		}
		SECTION("with not empty list") {
			list.PushBack(8);
			list.PushFront(6);
			list.PushBack(0);
			list.PopBack();
			list.PopFront();
			CHECK_THROWS(list.PopFront());
		}
	}