#include "ObjectGrid.h"


// -------------------------------------------------------------------------
// Grid Implementation
// -------------------------------------------------------------------------
#include <algorithm>
#include <cassert>

/// Returns the value divided by the divisor rounded up.
static int ceil_div(int value, int divisor)
{
	const int result = value / divisor;
	return (value % divisor != 0) ? (result + 1) : result;
}

ObjectGrid::ObjectGrid(int screen_w, int screen_h, int icell_w, int icell_h) :
	grid_w(ceil_div(screen_w, icell_w)), grid_h(ceil_div(screen_h, icell_h)),
	cell_w(icell_w), cell_h(icell_h), free_list(-1)
{
	cells.resize(grid_w * grid_h, -1);
}

ObjectGrid::ObjectGrid(const ObjectGrid& other) :
	grid_w(other.grid_w), grid_h(other.grid_h),
	cell_w(other.cell_w), cell_h(other.cell_h), free_list(-1)
{
	cells.resize(grid_w * grid_h, -1);
	for (int c = 0, num = size(); c < num; ++c)
	{
		// For each node in the other grid, insert its node element to this grid.
		for (const GridNode* node = other.first(c); node; node = other.next(node))
			insert_node(cells[c], node->element);
	}
}

int ObjectGrid::size() const
{
	return static_cast<int>(cells.size());
}

int ObjectGrid::width() const
{
	return grid_w;
}

int ObjectGrid::height() const
{
	return grid_h;
}

int ObjectGrid::cell_index(int px, int py) const
{
	const int cell_x = px / cell_w;
	const int cell_y = py / cell_h;
	return cell_y * grid_w + cell_x;
}

void ObjectGrid::insert(const int ltrb[4], int element)
{
	const int x1 = ltrb[0] / cell_w;
	const int y1 = ltrb[1] / cell_h;
	const int x2 = ltrb[2] / cell_w;
	const int y2 = ltrb[3] / cell_h;

	// Make sure the element rectangle is in bounds.
	assert(x1 >= 0 && x2 < grid_w && y1 >= 0 && y2 <= grid_h &&	"Element is out of bounds!");

	// For each grid cell that overlaps, insert the element.
	for (int y = y1; y <= y2; ++y)
	{
		int* cell_row = &cells[0] + y * grid_w;
		for (int x = x1; x <= x2; ++x)
			insert_node(cell_row[x], element);
	}
}

void ObjectGrid::insert_node(int& cell, int element)
{
	// See if we can pop a free node from the list.
	int node_index = free_list;
	if (node_index != -1)
		free_list = nodes[free_list].next;
	else
	{
		// If the free list was empty, add a new node.
		nodes.push_back(GridNode());
		node_index = (int)nodes.size() - 1;
	}

	// Set the node element to the one specified.
	nodes[node_index].element = element;

	// Push the node to the cell list.
	nodes[node_index].next = cell;
	cell = node_index;
}

void ObjectGrid::erase(const int ltrb[4], int element)
{
	const int x1 = ltrb[0] / cell_w;
	const int y1 = ltrb[1] / cell_h;
	const int x2 = ltrb[2] / cell_w;
	const int y2 = ltrb[3] / cell_h;

	// Make sure the element rectangle is in bounds.
	assert(x1 >= 0 && x2 < grid_w && y1 >= 0 && y2 <= grid_h && "Element is out of bounds!");

	// For each grid cell that overlaps, remove the element.
	for (int y = y1; y <= y2; ++y)
	{
		int* cell_row = &cells[0] + y * grid_w;
		for (int x = x1; x <= x2; ++x)
			erase_node(cell_row[x], element);
	}
}

void ObjectGrid::erase_node(int& cell, int element)
{
	// Walk the links until we find the node associated
	// with the element.
	int* link_ptr = &cell;
	while (nodes[*link_ptr].element != element)
	{
		link_ptr = &nodes[*link_ptr].next;
		//assert(*link_ptr != -1 && "Error: element was not found!");
		if (*link_ptr != -1)
			return;
	}

	// Capture the index of the next node in the cell.
	const int next_node = nodes[*link_ptr].next;

	// Push the node to the free list.
	nodes[*link_ptr].next = free_list;
	free_list = *link_ptr;

	// Just for debugging, set the element index to -1 to make
	// it easy to see which nodes have been removed.
#ifdef _DEBUG
	nodes[*link_ptr].element = -1;
#endif

	// Remove the node from the cell.
	*link_ptr = next_node;
}

const GridNode* ObjectGrid::first(int cell) const
{
	// Make sure we're accessing the grid in bounds.
	assert(cell >= 0 && cell < size() && "Out of bounds!");

	// Return the first node in the cell of null if empty.
	const int node_index = cells[cell];
	return node_index != -1 ? &nodes[node_index] : 0;
}

const GridNode* ObjectGrid::next(const GridNode* node) const
{
	// Return the next node in the cell of null if empty.
	return node->next != -1 ? &nodes[node->next] : 0;
}

void ObjectGrid::swap(ObjectGrid& other)
{
	// Swap all the fields between the two grids.
	cells.swap(other.cells);
	nodes.swap(other.nodes);
	std::swap(grid_w, other.grid_w);
	std::swap(grid_h, other.grid_h);
	std::swap(cell_w, other.cell_w);
	std::swap(cell_h, other.cell_h);
	std::swap(free_list, other.free_list);
}

