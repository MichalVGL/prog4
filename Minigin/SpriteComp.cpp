#include "SpriteComp.h"

#include <algorithm>

dae::SpriteComp::SpriteComp(dae::GameObject& parent)
	:Component{ parent }
{
	m_Entries.reserve(10);
	try
	{
		m_RenderComp.Init(GetOwner());
	}
	catch (const std::logic_error&)
	{
		std::cout << std::format("\nSpritecomp could't find the RenderComp on the GameObject, make sure to add RenderComp before SpriteComp!!!\n GameObject: {}\n\n", GetOwner().GetName());
		throw;
	}
}

//===================================================================================

void dae::SpriteComp::Update(float deltaTime)
{
	if (!m_pActiveEntry or m_Paused)
	{
		return;
	}

	int totalFrameCount = m_pActiveEntry->cols * m_pActiveEntry->rows - 1;
	bool loopComplete = m_FrameIndex > totalFrameCount;
	//if entry shouldn't loop and the loop is complete
	if (m_pActiveEntry->loop == false and loopComplete)
	{
		return;
	}

	m_Timer += deltaTime;
	if (m_SecondsPerFrame < m_Timer)
	{
		++m_FrameIndex;
		m_Timer = 0.f;
		if (m_FrameIndex > totalFrameCount)	//loop complete
		{
			if (m_pActiveEntry->loop == true)
			{
				m_FrameIndex = 0;
			}
			else
			{
				--m_FrameIndex;
				m_LoopComplete = true;
			}
		}
		SetCurrentFrame();
	}
}

//===================================================================================

// This function loads a texture into the RenderComp associated with the SpriteComp.
// It optionally clears existing sprite entries based on the keepExistingSpriteEntries flag.
// If a render key is already locked, it unlocks it before loading the new texture.
// After loading the texture, it locks the RenderComp to ensure exclusive control over the texture in the RenderComp.
void dae::SpriteComp::LoadTexture(const dae::TextureEntry& entry, bool keepExistingSpriteEntries)
{
	if (keepExistingSpriteEntries == false)
		m_Entries.clear();

	if (m_RenderKey != nullptr)
		m_RenderComp->Unlock(m_RenderKey);

	m_RenderComp->LoadImageTexture(entry);

	m_RenderKey = m_RenderComp->Lock();
}

void dae::SpriteComp::AddSpriteEntry(SpriteEntry entry)
{
	if (GetSpriteEntry(entry.id) != nullptr)
	{
		std::cout << std::format("Warning: tried adding a SpriteEntry that already exists. [GameObject {}]\n", GetOwner().GetName());
		return;
	}

	if (m_Entries.size() != m_Entries.capacity() or m_pActiveEntry == nullptr)
	{
		m_Entries.emplace_back(std::move(entry));
	}
	else	//if the vector will be resized and there is an active entry
	{
		//restore the active entry after reallocation
		sprite_id id = m_pActiveEntry->id;
		m_pActiveEntry = nullptr;
		m_Entries.emplace_back(std::move(entry));
		SetSpriteEntry(id);
	}
}

void dae::SpriteComp::DeleteSpriteEntry(sprite_id id)
{
	auto loc = std::find_if(m_Entries.begin(), m_Entries.end(),
		[&](const SpriteEntry& entry) { return entry.id == id; });

	if (loc != m_Entries.end())
	{
		if (loc->id == m_pActiveEntry->id)
			m_pActiveEntry = nullptr;

		m_Entries.erase(loc);
	}
	else
	{
		std::cout << std::format("Warning: tried deleting a SpriteEntry that doesn't exists. [GameObject {}]\n", GetOwner().GetName());
	}
}

void dae::SpriteComp::SetSpriteEntry(sprite_id id)
{
	auto loc = std::find_if(m_Entries.begin(), m_Entries.end(),
		[&](const SpriteEntry& entry) { return entry.id == id; });

	if (loc != m_Entries.end())
	{
		m_pActiveEntry = &(*loc);
		ResetLooping();
		SetCurrentFrame();
	}
	else
	{
		std::cout << std::format("Warning: tried setting a SpriteEntry active that doesn't exists. [GameObject {}]\n", GetOwner().GetName());
	}
}

const dae::SpriteEntry* dae::SpriteComp::GetSpriteEntry(sprite_id id) const
{
	auto loc = std::find_if(m_Entries.begin(), m_Entries.end(),
		[&](const SpriteEntry& entry) { return entry.id == id; });

	return loc != m_Entries.end() ? &(*loc) : nullptr;
}

void dae::SpriteComp::SetFPS(float fps)
{
	if (fps > 0.01f)
	{
		m_SecondsPerFrame = 1.f / fps;
	}
	else
	{
		std::cout << std::format("Warning: tried setting a negative fps on a sprite. [GameObject {}]\n", GetOwner().GetName());
	}
}

void dae::SpriteComp::Pause()
{
	m_Paused = true;
}

void dae::SpriteComp::Resume()
{
	m_Paused = false;
}

void dae::SpriteComp::SetFrame(int frame)
{
	//safety checks
	if (!m_pActiveEntry)
		return;

	ResetLooping();

	int max = m_pActiveEntry->cols * m_pActiveEntry->rows - 1;
	frame = std::clamp(frame, 0, max);

	m_FrameIndex = frame;
	SetCurrentFrame();
}

void dae::SpriteComp::FlipHorizontal(bool flip)
{
	m_RenderComp->SetHorizontalFlip(flip);
}

void dae::SpriteComp::FlipVertical(bool flip)
{
	m_RenderComp->SetVerticalFlip(flip);
}

bool dae::SpriteComp::IsLoopComplete() const
{
	return m_LoopComplete;
}

//===================================================================================

void dae::SpriteComp::ValidateEntry(SpriteEntry& entry)
{
	if (entry.cols <= 0)
	{
		std::cout << std::format("Validation failed: cols must be > 0 (got {}).\n", entry.cols);
		entry.cols = 1;
	}

	if (entry.rows <= 0)
	{
		std::cout << std::format("Validation failed: rows must be > 0 (got {}).\n", entry.rows);
		entry.rows = 1;
	}

	if (entry.srcRect.x < 0 || entry.srcRect.y < 0)
	{
		std::cout << std::format("Validation failed: srcRect must have positive position ({}x{}).\n", entry.srcRect.x, entry.srcRect.y);
		entry.srcRect.x = 0;
		entry.srcRect.y = 0;
	}

	if (entry.srcRect.w <= 0 || entry.srcRect.h <= 0)
	{
		std::cout << std::format("Validation failed: srcRect must have positive size ({}x{}).\n", entry.srcRect.w, entry.srcRect.h);
		entry.srcRect.w = 1;
		entry.srcRect.h = 1;
	}
}

void dae::SpriteComp::ResetLooping()
{
	m_LoopComplete = false;
	m_FrameIndex = 0;
	m_Timer = 0.f;
}

void dae::SpriteComp::SetCurrentFrame()
{
	if (!m_pActiveEntry)
		return;

	const int frameWidth = m_pActiveEntry->srcRect.w / m_pActiveEntry->cols;
	const int frameHeight = m_pActiveEntry->srcRect.h / m_pActiveEntry->rows;

	const int colIndex = m_FrameIndex % m_pActiveEntry->cols;
	const int rowIndex = m_FrameIndex / m_pActiveEntry->cols;

	Rect rect{
		.x = (colIndex * frameWidth) + m_pActiveEntry->srcRect.x,
		.y = (rowIndex * frameHeight) + m_pActiveEntry->srcRect.y,
		.w = frameWidth,
		.h = frameHeight
	};

	m_RenderComp->SetSrcRect(rect);
}