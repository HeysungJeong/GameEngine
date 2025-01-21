#include "Physics.h"

bool CheckAABBCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    // AABB 충돌 감지 로직
    if (rectA.x + rectA.w <= rectB.x) return false; // A의 오른쪽이 B의 왼쪽보다 왼쪽에 있다면
    if (rectA.x >= rectB.x + rectB.w) return false; // A의 왼쪽이 B의 오른쪽보다 오른쪽에 있다면
    if (rectA.y + rectA.h <= rectB.y) return false; // A의 아래쪽이 B의 위쪽보다 위에 있다면
    if (rectA.y >= rectB.y + rectB.h) return false; // A의 위쪽이 B의 아래쪽보다 아래에 있다면
    return true; // 위의 조건에 해당하지 않으면 충돌 중
}