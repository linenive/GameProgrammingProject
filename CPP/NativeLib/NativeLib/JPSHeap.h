
#include "Base.h"

struct JPSCoord {
	Int32 m_x = -1, m_y = -1;

public:
	JPSCoord() = default;
	JPSCoord(Int32 _x, Int32 _y) : m_x(_x), m_y(_y) {}

	void Add(const JPSCoord& rhs) { m_x += rhs.m_x; m_y += rhs.m_y; }
	void Clear() { m_x = -1; m_y = -1; }
	bool IsEmpty() { return (m_x == -1 && m_y == -1); }

	bool operator ==(const JPSCoord& C) const { return ((C.m_x == m_x) && (C.m_y == m_y)); }
	bool operator !=(const JPSCoord& C) const { return ((C.m_x != m_x) || (C.m_y != m_y)); }

	float DistanceSqrt(const JPSCoord& rhs) {
		float absX = abs(m_x - rhs.m_x);
		float absY = abs(m_y - rhs.m_y);

		float diagDist = std::min(absX, absY);
		float straightDist = std::max(absX, absY);
		return diagDist * 1.414213562373095f + straightDist;
	}
	Int32 GetX() { return m_x; }
};

struct JPSNode {
	typedef shared_ptr<JPSNode> SharedPtr;
	typedef std::weak_ptr<JPSNode> WeakPtr;

	JPSNode::SharedPtr	m_spParent = nullptr;
	JPSCoord m_Pos;
	char m_CardinalDir = 0;
	float m_Score = 0;
	float m_Heuri = 0;
	float m_Total = 0;

	JPSNode() = default;

	void Clear() {
		m_spParent = nullptr;
		m_Pos.Clear();
		m_Score = 0;
		m_Heuri = 0;
		m_Total = 0;
	}

	void Set(JPSNode::SharedPtr spParent, const JPSCoord& Pos, const JPSCoord& End, const char cardinalDir) {
		m_spParent = spParent;
		m_Pos = Pos;
		m_CardinalDir = cardinalDir;
		if (m_spParent) 
			m_Score = m_Pos.DistanceSqrt(m_spParent->m_Pos) + m_spParent->m_Score;
		else 
			m_Score = 0;
		m_Heuri = m_Pos.DistanceSqrt(End);

		//�θ�� �� ������ �Ÿ�(score) + ���� ������ ������ �Ÿ�(heuri)
		m_Total = m_Score + m_Heuri;
	}
};

class JPSHeap {
	std::vector<JPSNode::SharedPtr> m_Heap;

public:
	JPSHeap() = default;
	~JPSHeap() = default;

	void InsertNewone(JPSNode::SharedPtr value) {
		m_Heap.push_back(value);
		_ShiftUp(m_Heap.size() - 1);
	}

	bool InsertSmaller(JPSNode::SharedPtr value) {
		auto pSeg = m_Heap.data();
		auto cbSize = m_Heap.size();

		for (size_t n = 0; n < cbSize; ++n, ++pSeg) {

			// heap���� value�� ã��
			if (value->m_Pos != (*pSeg)->m_Pos)
				continue;

			// ���� ���� value�� total�� �� �۴ٸ� �װ����� �ٲ��ֱ� 
			if (value->m_Total >= (*pSeg)->m_Total) {
				return false;
			}
			else { // ���� ���� value�� total�� �� ũ�ٸ� 
				(*pSeg) = value;
				_ShiftUp(n);
				return true;
			}
		}
		return false;
	}

	JPSNode::SharedPtr PopMax() {
		auto result = m_Heap.front();
		m_Heap.front() = m_Heap.back();
		m_Heap.pop_back();
		_ShiftDown(0);
		return result;
	}

	const JPSNode::SharedPtr Max() const { return m_Heap.front(); }
	Int32 Count() const { return (Int32)m_Heap.size(); }
	void Clear() { m_Heap.clear(); }

private:
	typedef std::vector<JPSNode::SharedPtr>::size_type _heap_size_t;

	void _BuildHeap() {

		// Ʈ���� �� �ϴܺ��� ���� ����
		for (Int64 i = (Int64)(m_Heap.size() / 2); i >= 0; --i)
			_ShiftDown(i);
	}

	void _ShiftDown(_heap_size_t parent) {
		auto pSeg = m_Heap.data();
		auto cbSize = m_Heap.size();

		// �ڽ��� �ڽĵ��� �� ����, ���� ū ���� �� �ϴ����� ������ �۾�
		// ��带 ������ �� ���ų�, �� �̻� parent���� child���� ũ�� �ʾ� 
		// ���� �� ���ԵǸ� �ݺ��� �����. 
		for (;;) {
			auto left = static_cast<_heap_size_t>(parent * 2 + 1);
			if (left >= cbSize) break;

			auto right = left + 1;
			if (right < cbSize && pSeg[right]->m_Total < pSeg[left]->m_Total)
				left = right;

			if (pSeg[parent]->m_Total < pSeg[left]->m_Total)
				break;

			std::swap(pSeg[parent], pSeg[left]);
			parent = left;
		}
	}

	void _ShiftUp(_heap_size_t node) {

		auto pSeg = m_Heap.data();
		// ���� ��忡�� ������ �ö󰡸� �ݺ�
		while (node > 0)
		{
			auto parent = static_cast<_heap_size_t>((node - 1) / 2);

			// �� total���� �θ𺸴� ũ�ٸ� �ݺ��� �����
			if (pSeg[node]->m_Total > pSeg[parent]->m_Total)
				return;

			std::swap(pSeg[node], pSeg[parent]);
			node = parent;
		}
	}
};