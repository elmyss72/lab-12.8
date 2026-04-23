#include "pch.h"
#include "CppUnitTest.h"
#include "../lab12.8/lab12.8.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
    TEST_CLASS(UnitTest1)
    {
    public:

        Node* createList()
        {
            Node* head = nullptr;
            head = append(head, 1);
            head = append(head, 2);
            head = append(head, 3);
            head = append(head, 4);
            head = append(head, 5);
            return head;
        }

        TEST_METHOD(TestLoadStructure)
        {
            Node* head = createList();

            Assert::IsNotNull(head);
            Assert::AreEqual(1, head->data);

            deleteList(head);
        }

        TEST_METHOD(TestRemoveEven)
        {
            Node* head = createList();

            head = removeEven(head);

            Assert::AreEqual(1, head->data);
            Assert::AreEqual(3, head->next->data);
            Assert::AreEqual(5, head->next->next->data);

            Assert::IsNull(head->next->next->next);

            deleteList(head);
        }

        TEST_METHOD(TestDoubleOddValues)
        {
            Node* head = createList();
            head = removeEven(head);

            doubleOddValues(head);

            Assert::AreEqual(2, head->data);
            Assert::AreEqual(6, head->next->data);
            Assert::AreEqual(10, head->next->next->data);

            deleteList(head);
        }

        TEST_METHOD(TestInsertSublist)
        {
            Node* head = createList();

            Node* sub = nullptr;
            sub = append(sub, 100);
            sub = append(sub, 200);

            head = insertSublist(head, sub, 2);

            Assert::AreEqual(1, head->data);
            Assert::AreEqual(100, head->next->data);
            Assert::AreEqual(200, head->next->next->data);

            deleteList(head);
        }

        TEST_METHOD(TestFullProcess)
        {
            Node* head = createList();

            head = removeEven(head);
            doubleOddValues(head);

            Node* sub = nullptr;
            sub = append(sub, 7);
            sub = append(sub, 8);

            head = insertSublist(head, sub, 2);

            Assert::IsNotNull(head);
            Assert::AreEqual(2, head->data);

            deleteList(head);
        }
    };
}