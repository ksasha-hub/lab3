package main

import (
	"encoding/json"
	"fmt"
)

type btNode struct {
	value string
	left  *btNode
	right *btNode
}

type BinaryTree struct {
	root *btNode
	size int
}

func NewBinaryTree() *BinaryTree {
	return &BinaryTree{}
}

func (b *BinaryTree) Insert(value string) {
	if value == "" {
		return
	}
	var inserted bool
	b.root, inserted = b.insertRec(b.root, value)
	if inserted {
		b.size++
	}
}

func (b *BinaryTree) insertRec(node *btNode, value string) (*btNode, bool) {
	if node == nil {
		return &btNode{value: value}, true
	}

	if value < node.value {
		var inserted bool
		node.left, inserted = b.insertRec(node.left, value)
		return node, inserted
	} else if value > node.value {
		var inserted bool
		node.right, inserted = b.insertRec(node.right, value)
		return node, inserted
	}
	// If value == node.value, do nothing (no duplicates)
	return node, false
}

func (b *BinaryTree) Search(value string) bool {
	if value == "" {
		return false
	}
	return b.searchRec(b.root, value)
}

func (b *BinaryTree) searchRec(node *btNode, value string) bool {
	if node == nil {
		return false
	}

	if value == node.value {
		return true
	} else if value < node.value {
		return b.searchRec(node.left, value)
	} else {
		return b.searchRec(node.right, value)
	}
}

func (b *BinaryTree) Remove(value string) bool {
	if value == "" {
		return false
	}

	var removed bool
	b.root, removed = b.removeRec(b.root, value)
	if removed {
		b.size--
	}
	return removed
}

func (b *BinaryTree) removeRec(node *btNode, value string) (*btNode, bool) {
	if node == nil {
		return nil, false
	}

	var removed bool
	if value < node.value {
		node.left, removed = b.removeRec(node.left, value)
	} else if value > node.value {
		node.right, removed = b.removeRec(node.right, value)
	} else {
		// Node found
		if node.left == nil {
			return node.right, true
		} else if node.right == nil {
			return node.left, true
		}

		// Node with two children
		minNode := b.findMin(node.right)
		node.value = minNode.value
		node.right, _ = b.removeRec(node.right, minNode.value)
		removed = true
	}
	return node, removed
}

func (b *BinaryTree) findMin(node *btNode) *btNode {
	if node == nil {
		return nil
	}
	for node.left != nil {
		node = node.left
	}
	return node
}

func (b *BinaryTree) findMax(node *btNode) *btNode {
	if node == nil {
		return nil
	}
	for node.right != nil {
		node = node.right
	}
	return node
}

func (b *BinaryTree) GetRoot() (string, bool) {
	if b.root == nil {
		return "", false
	}
	return b.root.value, true
}

func (b *BinaryTree) GetMin() (string, bool) {
	minNode := b.findMin(b.root)
	if minNode == nil {
		return "", false
	}
	return minNode.value, true
}

func (b *BinaryTree) GetMax() (string, bool) {
	maxNode := b.findMax(b.root)
	if maxNode == nil {
		return "", false
	}
	return maxNode.value, true
}

func (b *BinaryTree) Height() int {
	return b.heightRec(b.root)
}

func (b *BinaryTree) heightRec(node *btNode) int {
	if node == nil {
		return 0
	}

	leftHeight := b.heightRec(node.left)
	rightHeight := b.heightRec(node.right)

	if leftHeight > rightHeight {
		return leftHeight + 1
	}
	return rightHeight + 1
}

func (b *BinaryTree) Size() int {
	return b.size
}

func (b *BinaryTree) IsEmpty() bool {
	return b.size == 0
}

func (b *BinaryTree) Clear() {
	b.root = nil
	b.size = 0
}

func (b *BinaryTree) InOrder() []string {
	result := make([]string, 0, b.size)
	b.inOrderRec(b.root, &result)
	return result
}

func (b *BinaryTree) inOrderRec(node *btNode, result *[]string) {
	if node != nil {
		b.inOrderRec(node.left, result)
		*result = append(*result, node.value)
		b.inOrderRec(node.right, result)
	}
}

func (b *BinaryTree) PreOrder() []string {
	result := make([]string, 0, b.size)
	b.preOrderRec(b.root, &result)
	return result
}

func (b *BinaryTree) preOrderRec(node *btNode, result *[]string) {
	if node != nil {
		*result = append(*result, node.value)
		b.preOrderRec(node.left, result)
		b.preOrderRec(node.right, result)
	}
}

func (b *BinaryTree) PostOrder() []string {
	result := make([]string, 0, b.size)
	b.postOrderRec(b.root, &result)
	return result
}

func (b *BinaryTree) postOrderRec(node *btNode, result *[]string) {
	if node != nil {
		b.postOrderRec(node.left, result)
		b.postOrderRec(node.right, result)
		*result = append(*result, node.value)
	}
}

func (b *BinaryTree) LevelOrder() []string {
	if b.root == nil {
		return []string{}
	}

	result := make([]string, 0, b.size)
	queue := []*btNode{b.root}

	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]
		result = append(result, node.value)

		if node.left != nil {
			queue = append(queue, node.left)
		}
		if node.right != nil {
			queue = append(queue, node.right)
		}
	}
	return result
}

func (b *BinaryTree) Print() {
	fmt.Printf("BinaryTree(size=%d, height=%d): ", b.size, b.Height())
	fmt.Printf("InOrder: %v\n", b.InOrder())
}

func (b *BinaryTree) Serialize() ([]byte, error) {
	values := b.LevelOrder()
	return json.Marshal(values)
}

func (b *BinaryTree) Deserialize(data []byte) error {
	var values []string
	if err := json.Unmarshal(data, &values); err != nil {
		return err
	}

	b.Clear()
	for _, value := range values {
		if value != "" {
			b.Insert(value)
		}
	}
	return nil
}

// SerializeBinary сериализует дерево в бинарный формат
func (b *BinaryTree) SerializeBinary() ([]byte, error) {
	type TreeData struct {
		Size   int
		Values []string
	}

	treeData := TreeData{
		Size:   b.size,
		Values: b.LevelOrder(),
	}

	return serializeToBinary(treeData)
}

// DeserializeBinary десериализует дерево из бинарного формата
func (b *BinaryTree) DeserializeBinary(data []byte) error {
	type TreeData struct {
		Size   int
		Values []string
	}

	var treeData TreeData
	if err := deserializeFromBinary(data, &treeData); err != nil {
		return err
	}

	b.Clear()
	for _, value := range treeData.Values {
		if value != "" {
			b.Insert(value)
		}
	}
	return nil
}
