#pragma once
#include <queue>
#include <vector>
#include <MiniKit/Graphics/Numerics.hpp>
#include "Components/MapTileRenderer.hpp"

using Float2 = ::MiniKit::Graphics::float2;
using Uint2 = ::MiniKit::Graphics::uint2;

namespace GameEngine
{
	struct Node
	{
		Node() : pos({0.0f, 0.0f}), parent({ -1.0f, -1.0f }), f(0), g(0) {}
		Node(const Float2& pos, uint32_t f) : pos(pos), parent({ -1.0f, 1.0f }), f(f), g(0) {}
		Node(const Float2& pos, const Float2& parent, uint32_t f, uint32_t g) : pos(pos), parent(parent), f(f), g(g) {}

		Float2 pos;
		Float2 parent;
		uint32_t f; // the sum of g and the estimated movement cost to move from that given square on the grid to the final destination
		uint32_t g; // the movement cost to move from the starting point to a given square on the grid
	};

	// Reverse std::priority_queue to get the smallest element on top
	inline bool operator< (const Node& a, const Node& b) { return a.f > b.f; }
	
	class AStar
	{
	public:
		AStar();

		::std::vector<Float2> findPath(const Float2& startPos, const Float2& targetPos);
		void loadGrid(::std::vector<ECS::MapTileRenderer::Transform>& grid, Uint2 dimensions);
	
	private:
		bool isValid(const Float2& pos) const;
		bool isBlocked(int index) const;
		uint32_t convertTo1D(const Float2& pos) const;
		::std::vector<Float2> buildPath() const;
		
		[[nodiscard]] uint32_t heuristicManhattan(const Float2& p1, const Float2& p2) const;
		[[nodiscard]] uint32_t heuristicEuclidean(const Float2& p1, const Float2& p2) const;
	
		uint32_t size_; // number of tiles in map
		Uint2 dimensions_; // height and weight of map
		Float2 startPos_;
		Float2 targetPos_;
		
		::std::priority_queue<Node> openList_; // nodes to visit
		::std::vector<bool> closedList_; // visited nodes
		::std::vector<Node> cameFrom_; // backward connections
		
		::std::vector<::MiniKit::Graphics::float2> directions_;
		::std::vector<ECS::MapTileRenderer::Transform> grid_;

	};
	
}
