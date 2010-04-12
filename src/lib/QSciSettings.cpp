/*
JuffEd - An advanced text editor
Copyright 2007-2010 Mikhail Murzin

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License 
version 2 as published by the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "QSciSettings.h"

bool QSciSettings::get(BoolKey key) {
	switch (key) {
		case ShowIndents :
			return Settings::boolValue("QSci", "showIndents");
		
		case HighlightMatchingBrace :
			return Settings::boolValue("QSci", "highlightMatchingBrace");
		
		case HighlightCurLine :
			return Settings::boolValue("QSci", "highlightCurLine");
		
		case HighlightCurWord :
			return Settings::boolValue("QSci", "highlightCurWord");
		
		
	}
	return false;
}

QColor QSciSettings::get(ColorKey key) {
	switch (key) {
		case MatchingBraceBgColor :
		{
			QColor c = Settings::value("QSci", "matchingBraceBgColor").value<QColor>();
			return c.isValid() ? c : defaultValue("QSci", "matchingBraceBgColor").value<QColor>();
		}
		case IndentsColor :
		{
			QColor c = Settings::value("QSci", "indentsColor").value<QColor>();
			return c.isValid() ? c : defaultValue("QSci", "indentsColor").value<QColor>();
		}
		case WordHLColor :
		{
			QColor c = Settings::value("QSci", "wordHLColor").value<QColor>();
			return c.isValid() ? c : defaultValue("QSci", "wordHLColor").value<QColor>();
		}
		case CurLineColor :
		{
			QColor c = Settings::value("QSci", "curLineColor").value<QColor>();
			return c.isValid() ? c : defaultValue("QSci", "curLineColor").value<QColor>();
		}
	}
	return QColor();
}



void QSciSettings::set(BoolKey key, bool value) {
	switch (key) {
		case ShowIndents:
			Settings::setValue("QSci", "showIndents", value);
			break;
	}
}

void QSciSettings::set(ColorKey key, const QColor& c) {
	switch (key) {
		case MatchingBraceBgColor :
			Settings::setValue("QSci", "matchingBraceBgColor", c);
			break;
		
		case IndentsColor :
			Settings::setValue("QSci", "indentsColor", c);
			break;
		
		case WordHLColor :
			Settings::setValue("QSci", "wordHLColor", c);
			break;
		
		case CurLineColor :
			Settings::setValue("QSci", "curLineColor", c);
			break;
	}
}