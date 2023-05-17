#include "CDrawable.hpp"

CDrawable::CDrawable() : sortOrder(0), layer(DrawLayer::Default) {}
CDrawable::~CDrawable() {}
void CDrawable::SetSortOrder(int order) { sortOrder = order; }
int CDrawable::GetSortOrder() const { return sortOrder; }
void CDrawable::SetDrawLayer(DrawLayer drawLayer) { layer = drawLayer; }
DrawLayer CDrawable::GetDrawLayer() const { return layer; }