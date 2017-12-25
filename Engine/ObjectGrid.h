#pragma once

#include <vector>

// -------------------------------------------------------------------------
// Grid Interface
// -------------------------------------------------------------------------
/// Represents a node in the grid.
struct GridNode
{
	// Stores either the next node in the grid cell or the next free
	// node if this node has been removed.
	int next;

	// Stores the index to the element.
	int element;
};



/// Partitions elements into grid cells to accelerate searches for nearby
/// elements, collision detection, figuring out what element is under a
/// mouse cursor, etc.
class ObjectGrid
{
public:
	// Creates a grid partitioner. 'screen_w' and 'screen_h' represent
	// the size of the screen in pixels. 'cell_w' and 'cell_h' represent
	// size of a single cell in pixels.
	ObjectGrid(int screen_w, int screen_h, int cell_w, int cell_h);

	/// Creates a copy of the specified grid. The new copy will have its
	/// nodes arranged in a way such that they are contiguous within a
	/// given cell.
	ObjectGrid(const ObjectGrid& other);

	/// @return The number of cells in the grid.
	int size() const;

	/// @return The width of the grid (number of columns).
	int width() const;

	/// @return The height of the grid (number of rows).
	int height() const;

	/// @return The cell index for the specified point in pixel coordinates.
	int cell_index(int px, int py) const;

	// Inserts an element to the grid. 'ltrb' represent the left, top,
	// right, and bottom pixel coordinates.
	void insert(const int ltrb[4], int element);

	// Removes the element to the grid. 'ltrb' represent the left, top,
	// right, and bottom pixel coordinates.
	void erase(const int ltrb[4], int element);

	// Returns the first node at the specified cell index.
	const GridNode* first(int cell) const;

	// Returns the next node in the same cell to the one specified.
	const GridNode* next(const GridNode* node) const;

	/// Swaps the contents of this grid with the one specified.
	void swap(ObjectGrid& other);

private:
	// Inserts a node with the specified element to the specified cell.
	void insert_node(int& cell, int element);

	// Removes the node with the specified element from the specified cell.
	void erase_node(int& cell, int element);

	// Stores all the cells in the grid.
	std::vector<int> cells;

	// Stores all the nodes in the grid.
	std::vector<GridNode> nodes;

	/// Stores the width of the grid in cells (number of columns).
	int grid_w;

	/// Stores the height of the grid in cells (number of rows).
	int grid_h;

	// Stores the width of a cell in pixels.
	int cell_w;

	// Stores the height of a cell in pixels.
	int cell_h;

	// Stores an index to the first free (unused) node.
	int free_list;
};
