#pragma once

#include "stdafx.h"

class Interface : public Sprite
{
private:
	Sprite* _button;
	bool _isOn;

	Sprite* _water_back;
	Sprite* _food_back;
	Sprite* _human_back;
	Sprite* _medicine_back;

	ProgressTimer* water_gage;
	ProgressTimer* food_gage;
	ProgressTimer* human_gage;
	ProgressTimer* medicine_gage;

	Label* _water_label;
	Label* _food_label;
	Label* _human_label;
	Label* _medicine_label;
private:
	void OnOff();
public:
	static Interface* create(Node* parent);
	
	void Init();
	void SetOnTouch(Touch* touch);

	void SetWater(float curValue, float maxValue);
	void SetFood(float curValue, float maxValue);
	void SetHuman(float curValue, float maxValue);
	void SetMedicine(float curValue, float maxValue);
};