#ifndef LIST_H
#define LIST_H

#include <memory>
#include <assert.h>
#include <exception>

template<typename T>
class List
{
    struct LinkedList
    {
        T first;
        std::shared_ptr<LinkedList> rest;
        LinkedList(const T value) : first(value),
                                    rest(nullptr)
        {
        }

        LinkedList(const T value, std::shared_ptr<LinkedList> next) : first(value), rest(next)
        {
        }
    };
    std::shared_ptr<LinkedList> m_list;

    List(std::shared_ptr<List<T>::LinkedList> list) : m_list(list)
    {
    }

public:

    List() : m_list(nullptr)
    {
    }

    List(const List<T>& list) : m_list(list.m_list)
    {
    }

    inline bool empty()
    {
        return m_list == nullptr;
    }

    List& operator=(const List& other)
    {
        m_list = other.m_list;
        return (*this);
    }

    explicit List(const T value) : m_list(std::make_shared<LinkedList>(value))
    {
        assert(!empty());
    }

    const T first()
    {
        if(m_list == nullptr)
        {
            assert(size() == 0);
            throw std::runtime_error("Prázdný list!");
        }
        return m_list->first;
    }

    List<T> rest()
    {
        if(m_list != nullptr)
        {
            return List(m_list->rest);
        }
        return List();
    }

    size_t size()
    {
        List<T> it = *this;
        size_t sizeOfList = 0;
        while(!it.empty())
        {
            it = it.rest();
            sizeOfList++;
        }
        return sizeOfList;
    }

    T last()
    {
        if(empty())
        {
            throw std::runtime_error("Prázdný list!");
        }
        auto it = *this;
        while(!it.rest().empty())
        {
            it = it.rest();
        }
        return it.first();
    }

    List<T> addBack(T value)
    {
        if(empty())
        {
            return List(value);
        }
        else
        {
            auto newList = List(value);
            auto stack = List();
            auto it = (*this);
            while(!it.empty())
            {
               stack = stack.add(it.first());
               it = it.rest();
            }
            while(!stack.empty())
            {
                newList = newList.add(stack.first());
                stack = stack.rest();
            }
            return newList;
        }
        return List();
    }

    List<T> add(T value)
    {
        List newList(value);
        newList.m_list->rest = m_list;
        return newList;
    }
};

#endif // LIST_H
