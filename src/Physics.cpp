#include "Physics.h"

bool CheckAABBCollision(const SDL_Rect& rectA, const SDL_Rect& rectB) {
    // AABB �浹 ���� ����
    if (rectA.x + rectA.w <= rectB.x) return false; // A�� �������� B�� ���ʺ��� ���ʿ� �ִٸ�
    if (rectA.x >= rectB.x + rectB.w) return false; // A�� ������ B�� �����ʺ��� �����ʿ� �ִٸ�
    if (rectA.y + rectA.h <= rectB.y) return false; // A�� �Ʒ����� B�� ���ʺ��� ���� �ִٸ�
    if (rectA.y >= rectB.y + rectB.h) return false; // A�� ������ B�� �Ʒ��ʺ��� �Ʒ��� �ִٸ�
    return true; // ���� ���ǿ� �ش����� ������ �浹 ��
}