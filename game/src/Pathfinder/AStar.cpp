#include "AStar.hpp"

namespace GameEngine
{
	AStar::AStar() :
		size_(0),
		dimensions_({ 0, 0 }),
		startPos_({ 0.0f, 0.0f }),
		targetPos_({ 0.0f, 0.0f })
	{
		directions_ = { { -1, 0 }, { 1, 0 }, { 0, 1 }, { 0, -1 } };
	}

	::std::vector<Float2> AStar::findPath(const Float2& startPos, const Float2& targetPos)
	{
		startPos_ = startPos;
		targetPos_ = targetPos;
		cameFrom_.resize(size_);
		closedList_.resize(size_, false);

		cameFrom_[convertTo1D(startPos)].parent = startPos;
		openList_.push(Node(startPos, 0));

		uint32_t fNew, gNew;

		while (!openList_.empty())
		{
			// Get the node with the least f value
			Float2 currentPos = openList_.top().pos;

			if (currentPos.x == targetPos_.x && currentPos.y == targetPos_.y)
			{
				break;
			}

			openList_.pop();
			// node was visited
			closedList_[convertTo1D(currentPos)] = true;

			// Check the neighbor positions of the current node
			
			for (auto dir : directions_)
			{
				Float2 neighborPos;
				neighborPos.x = { currentPos.x + dir.x };
				neighborPos.y = { currentPos.y + dir.y };
				const auto neighborIndex = convertTo1D(neighborPos);

				if (!isValid(neighborPos) || isBlocked(neighborIndex) || closedList_[neighborIndex] == true)
				{
					continue;
				}

				gNew = cameFrom_[convertTo1D(currentPos)].g + 1; // in current case move by one tile
				fNew = gNew + heuristicManhattan(neighborPos, targetPos_);

				if (cameFrom_[neighborIndex].f == 0 || fNew < cameFrom_[neighborIndex].f)
				{
					openList_.push(Node(neighborPos, fNew));
					cameFrom_[neighborIndex] = { {neighborPos.x, neighborPos.y}, {currentPos.x, currentPos.y}, fNew, gNew };
				}
			}
		}
		return buildPath();
	}

	::std::vector<Float2> AStar::buildPath() const
	{
		::std::vector<Float2> path;
		auto currentPos = targetPos_;
		auto currentIndex = convertTo1D(currentPos);
		
		// go through 
		while (!(cameFrom_[currentIndex].parent.x == currentPos.x && cameFrom_[currentIndex].parent.y == currentPos.y))
		{
			path.push_back(currentPos);
			currentPos = cameFrom_[currentIndex].parent;
			currentIndex = convertTo1D(currentPos);
		}
		std::reverse(path.begin(), path.end());
		
		return path;
	}

	void AStar::loadGrid(::std::vector<ECS::MapTileRenderer::Transform>& grid, Uint2 dimensions)
	{
		grid_ = grid;
		dimensions_ = { dimensions };
		size_ = dimensions.x * dimensions.y;
	}

	bool AStar::isValid(const Float2& pos) const
	{
		return (pos.x >= 0) && (pos.x < dimensions_.x) &&
			(pos.y >= 0) && (pos.y < dimensions_.y);
	}
	
	bool AStar::isBlocked(int index) const
	{
		return (grid_[index].collidable);
	}
	
	uint32_t AStar::convertTo1D(const Float2& pos) const
	{
		return static_cast<uint32_t>(pos.y * dimensions_.x + pos.x);
	}


	uint32_t AStar::heuristicManhattan(const Float2& p1, const Float2& p2) const
	{
		return static_cast<uint32_t>(std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y));
	}

	uint32_t AStar::heuristicEuclidean(const Float2& p1, const Float2& p2) const
	{
		const Float2 dist = {float{std::abs(p1.x - p2.x)}, float{std::abs(p1.y - p2.y)}};
		return static_cast<uint32_t>(sqrt(dist.x * dist.x + dist.y * dist.y));
	}
}
