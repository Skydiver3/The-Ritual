// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <string>
#include "GeometricRecognizerTypes.h"

using namespace std;
namespace DollarRecognizer
{
	class THERITUAL_API GestureTemplate
	{
	public:
		GestureTemplate();
		~GestureTemplate();

		string name;
		Path2D points;

		GestureTemplate(string _name, Path2D _points)
		{
			this->name = _name;
			this->points = _points;
		}
	};

	typedef vector<GestureTemplate> GestureTemplates;
}
