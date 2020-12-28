/* This file is part of LeagueSkinChanger by b3akers, licensed under the MIT license:
*
* MIT License
*
* Copyright (c) b3akers 2020
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include <Windows.h>
#include "driver.h"
#include "PIDManager.h"

void InitThread() {
	PIDManager _PIDManager;
	m_pid = _PIDManager.GetAowProcId();

	if (m_pid) {
		Controller = new DriverController(m_pid);

		usermode_pid = GetCurrentProcessId();

		if (usermode_pid) {
			//printf(("> usermode_pid: %d\n"), usermode_pid);

			m_base = GetBaseAddress();

			if (m_base) {
				//printf(("> m_pid: %d base: 0x%llx\n"), m_pid, m_base);
			}
		}
	}

	//DO SOMETHING LIKE
	Controller->GetProcessBase();
	//OR
	Controller->ReadUInt32(0x0);
}

BOOL APIENTRY DllMain( HMODULE h_module,
	DWORD  ul_reason_for_call,
	LPVOID lp_reserved
) {
	switch ( ul_reason_for_call ) {
		case DLL_PROCESS_ATTACH:
			DisableThreadLibraryCalls( h_module );
			CreateThread( NULL, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(InitThread), NULL, 0, NULL );
			break;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
	}
	return TRUE;
}

