#pragma once

#include "Block.h"

class BlockOccludable
{
public:
    BlockOccludable(Block* block)
        : m_Block(block) {
    }

    VECTOR GetPos() const
    {
        return m_Block->GetPos();
    }

    void SetAlpha(int alpha)
    {
       // m_Block->SetAlpha(alpha);
    }

private:
    Block* m_Block;
};