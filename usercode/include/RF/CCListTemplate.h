/* 
 * File:   CCListTemplate.h
 * Author: guiyuliang
 *
 * Created on 2020年9月4日, 上午9:04
 * 模板类的声明和实现需要放在同一个文件中，否则会编译时会报错.
 */
#pragma once
#ifndef CCLISTTEMPLATE_H
#define	CCLISTTEMPLATE_H

#include "stddef.h"

#ifndef NULL
#define NULL    (void*)0
#endif

template <class T>
class CCNode
{
public:
    CCNode<T> *next;
    CCNode<T> *prev;
    T data;
};

template <class T>
class CCList
{
public:
    CCList();
    CCList(const CCList& ccList);
    virtual ~CCList();
public:
    void Add(T element);
    T Find(int index);
    T* GetAddress(int index);
    void Remove(T element);
    void RemoveAll();
    bool IsEmpty();
    int Size();
    
    T& operator [](int index);
private:
    CCNode<T> *head;
    CCNode<T> *tail;
    int nLength;
};
/*********************************************************************************/
template <typename T>
CCList<T>::CCList()
{
    head = new CCNode<T>;
    tail = new CCNode<T>;
    
    head->next = tail;
    head->prev = NULL;
    
    tail->next = NULL;
    tail->prev = head;
    
    nLength = 0;
}

template <typename T>
CCList<T>::CCList(const CCList& ccList)
{
    head = new CCNode<T>;
    tail = new CCNode<T>;
    head->prev = NULL;
    head->next = tail;
    tail->prev = head;
    nLength = 0;
    CCNode<T>* temp = ccList.head;
    while(temp.next != ccList.tail)
    {
        temp = temp->next;
        tail->data = temp->data;
        CCNode<T> *p = new CCNode<T>;
        p->prev = tail;
        tail->next = p;
        tail = p;
        nLength++;
    }
    tail->next = NULL;
}

template <typename T>
CCList<T>::~CCList()
{
    if(nLength == 0)
    {
        delete head;
        delete tail;
        
        head = NULL;
        tail = NULL;
    }
    else
    {
        while(head->next != NULL)
        {
            CCNode<T> *temp = head;
            head = head->next;
            delete temp;
        }
        delete head;
        head = NULL;
        nLength = 0;
    }
}

//Add
template <typename T>
void CCList<T>::Add(T element)
{
    tail->data = element;
    tail->next = new CCNode<T>;
    
    CCNode<T>* p = tail;
    
    tail = tail->next;
    tail->prev = p;
    tail->next = NULL;
    nLength++;
}

//Find element
template <typename T>
T CCList<T>::Find(int index)
{
    if(nLength == 0)
    {
        return head->next->data;
    }
    if(index >= nLength)
    {
        return tail->prev->data;
    }
    
    int nIndex = 0;
    CCNode<T>* p;
    if(index < nLength / 2)
    {
        p = head->next;
        while((p->next != NULL) &&(nIndex ++ < index))
        {
            p = p->next;
        }
    }
    else
    {
        p = tail->prev;
        while((p->prev != NULL) &&(nIndex ++ < (nLength - index -1)))
        {
            p = p->prev;
        }
    }
    return p->data;
}

template <typename T>
T& CCList<T>::operator [](int index)
{
    int nIndex = 0;
    CCNode<T>* p;
    if(index < nLength / 2)
    {
        p = head->next;
        while((p->next != NULL) &&(nIndex ++ < index))
        {
            p = p->next;
        }
    }
    else
    {
        p = tail->prev;
        while((p->prev != NULL) &&(nIndex ++ < (nLength - index -1)))
        {
            p = p->prev;
        }
    }
    return p->data;
}

//Get address
template <typename T>
T* CCList<T>::GetAddress(int index)
{
    if(nLength == 0)
    {
        return &head->next->data;
    }
    if(index >= nLength)
    {
        return &tail->prev->data;                
    }
    
    int nIndex = 0;
    CCNode<T>* p;
    if(index < nLength / 2)
    {
        p = head->next;
        while((p->next != NULL) &&(nIndex ++ < index))
        {
            p = p->next;
        }
    }
    else
    {
        p = tail->prev;
        while((p->prev != NULL) &&(nIndex ++ < (nLength - index -1)))
        {
            p = p->prev;
        }
    }
    return &p->data;
}

//Delete element
template <typename T>
void CCList<T>::Remove(T element)
{
    if(nLength == 0)
    {
        return;
    }
    CCNode<T> *p = head;
    while(p->next != NULL)
    {
        p = p->next;
        if(p->data == element)
        {
            CCNode<T> *temp = p->prev;
            temp->next = p->next;
            p->next->prev = temp;
            
            delete p;
            nLength--;
            
            break;
        }
    }
}

//Remove All
template <typename T>
void CCList<T>::RemoveAll()
{
    if(nLength == 0)
    {
        return;
    }
    CCNode<T> *p = head->next;
    while(p != tail)
    {
        CCNode<T>* temp = p;
        p = p->next;
        delete temp;
    }
    head->next = tail;
    tail->prev = head;
    nLength = 0;
}

template <typename T>
bool CCList<T>::IsEmpty()
{
    return (nLength == 0?true:false);
}

template <typename T>
int CCList<T>::Size()
{
    return nLength;
}

/**********************************************************/
#endif	/* CCLISTTEMPLATE_H */

