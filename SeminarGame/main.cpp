#include <raylib.h>
#include "Sequence.h"
#include "Title.h"



int main()
{
	/* Window�̏����� */
	int WindowWidth = 960;
	int WindowHeight = 480;	
	InitWindow(WindowWidth, WindowHeight, "SeminarProject");
	SetTargetFPS(60); // 60FPS
	SetWindowState(FLAG_VSYNC_HINT); // ��������ON

	// �V�[�P���X������
	Sequence* currentSequence = new Title();

	// ���C�����[�v
	while (!WindowShouldClose())
	{
		/* ���� */
		currentSequence->input();
		
		/* �X�V */
		currentSequence->update();

		/* �`�� */
		DrawFPS(10, 20); // FPS��\�� �����Ă�����
		currentSequence->draw();

		// �V�[�P���X�؂�ւ�
		Sequence* next = currentSequence->nextSequence();
		if (next != nullptr) {
			currentSequence->unloadData();
			delete currentSequence;
			currentSequence = next;
		}
	}
	
	currentSequence->unloadData();
	delete currentSequence;
	currentSequence = 0;

	CloseWindow();
	return 0;
}
