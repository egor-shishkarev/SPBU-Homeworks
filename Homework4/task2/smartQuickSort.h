#pragma once

// ��� ������� ������������� ���������� ���������, ������� �������� qsort �������� ������� �� ��������� �������� �������. �������������� �������.
// ��������� �� ���� ��������� �� ������, ������ ������ (������ 0, ���� ����� ������������� ���� ������) - ������ � �������� ����� ������ ����������,
// ��������� ������ - ������ ����� �������. �� ���������� ������, ���� ��������� ��� ������.
int insertionSort(int* arrayOfNumbers, const int firstIndex, const int lastIndex);

// �������� ������� ��������� quick sort, ����������� ����������� ���������, ��� ����� ����������� ������.
// ��������� �� ���� ��������� �� ������, ������ � ��������� ������, ��� �� ��� � � ������� insertionSort().
// ������� ����, ���� ���������� ������ �������.
int smartQuickSort(int* arrayOfNumbers, int firstIndex, int lastIndex);
