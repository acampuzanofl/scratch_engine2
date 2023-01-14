#include "CDrawable.hpp"

CDrawable::CDrawable() : sortOrder(0) {}
CDrawable::~CDrawable() {}
void CDrawable::SetSortOrder(int order) { sortOrder = order; }
int CDrawable::GetSortOrder() const { return sortOrder; }
