#ifndef TREETESTINGFUNCTIONS_CPP_H
#define TREETESTINGFUNCTIONS_CPP_H

#include "../Core/RBBSTree.h"

void RBBSTreeTest(const RBBSTree<SerializableObject> &input, const std::string &expected, const std::string &testName);

void RBBSInsertionWhenEmptiedTest(RBBSTree<SerializableObject> &tree, const SerializableObject &input,
                                  const std::string &expectedInside);

void RBBSTreeDeletionWhenEmptiedTest(RBBSTree<SerializableObject> &tree);

template<class T>
void
RBBSTreeFilterTest(const RBBSTree<SerializableObject> &tree, const std::string &expected, const std::string &testName);

void RBBSTreeSearchTest(const std::vector<const SerializableObject *> input, const std::string &expected,
                        const std::string &testName);

#endif //TREETESTINGFUNCTIONS_CPP_H
