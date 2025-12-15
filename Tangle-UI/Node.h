#ifndef NODE_H
#define NODE_H
#pragma once
#include <QString>

class Node
{
public:
    QString text;
    int id;
    Node* next;

    Node(const QString &t, int identifier)
        : text(t), id(identifier), next(nullptr) {}
};

#endif // NODE_H
