#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <XInput.h>
#pragma comment(lib, "xinput.lib")

#include "XboxController.h"

using namespace dae;

class XBox360Controller::XBox360ControllerImpl final
{
public:

    XBox360ControllerImpl(unsigned int controllerIndex)
        :m_ControllerIndex{controllerIndex},
        m_Active{true}
    {
        ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
        ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
    }

    void Update()
    {
        if (m_Active)
        {
            CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
            ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
            XInputGetState(m_ControllerIndex, &m_CurrentState);
            auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
            m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
            m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);
        }
    }

    static bool IsConnected(int controllerIndex)
    {
        XINPUT_STATE state;
        ZeroMemory(&state, sizeof(XINPUT_STATE));
        DWORD result = XInputGetState(controllerIndex, &state);
        return result == ERROR_SUCCESS;
    }

    void SetActive(bool active)
    {
        m_Active = active;
        if (!active)
        {
            ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
            ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
        }
    }

    bool IsDownThisFrame(unsigned int button) const { return m_ButtonsPressedThisFrame & button; }
    bool IsUpThisFrame(unsigned int button) const { return m_ButtonsReleasedThisFrame & button; }
    bool IsPressed(unsigned int button) const { return m_CurrentState.Gamepad.wButtons & button; }

    unsigned int GetIndex() const { return m_ControllerIndex; }
private:

    XINPUT_STATE m_PreviousState{};
    XINPUT_STATE m_CurrentState{};
    WORD m_ButtonsPressedThisFrame{};
    WORD m_ButtonsReleasedThisFrame{};
    unsigned int m_ControllerIndex;
    bool m_Active;
};

XBox360Controller::XBox360Controller(unsigned int controllerIndex)
{
    m_pImpl = new XBox360ControllerImpl(controllerIndex);
}

XBox360Controller::~XBox360Controller()
{
    delete m_pImpl;
}

void XBox360Controller::Update()
{
    m_pImpl->Update();
}

bool XBox360Controller::IsDown(ControllerButton button) const
{
    return m_pImpl->IsDownThisFrame(static_cast<unsigned int>(button));
}

bool XBox360Controller::IsUp(ControllerButton button) const
{
    return m_pImpl->IsUpThisFrame(static_cast<unsigned int>(button));
}

bool XBox360Controller::IsPressed(ControllerButton button) const
{
    return m_pImpl->IsPressed(static_cast<unsigned int>(button));
}

bool XBox360Controller::IsConnected(int controllerIndex)
{
    return XBox360ControllerImpl::IsConnected(controllerIndex);
}

unsigned int XBox360Controller::GetIndex() const
{
    return m_pImpl->GetIndex();
}

void XBox360Controller::SetActive(bool active)
{
    m_pImpl->SetActive(active);
}

//bool XBox360Controller::IsConnected()
    //{
    //    // reset controller state
    //    ZeroMemory(&m_ControllerState, sizeof(XINPUT_STATE));
    //    DWORD result = XInputGetState(m_ControllerIndex, &m_ControllerState);
    //    if (result == ERROR_SUCCESS)
    //    {
    //        return true;
    //    }
    //    else
    //    {
    //        return false;
    //    }
    //}
    //void XBox360Controller::Vibrate(int leftVal, int rightVal)
    //{
    //    // Create a Vibraton State
    //    XINPUT_VIBRATION Vibration;
    //    // reset vibration state
    //    ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));
    //    // Set the Vibration Values
    //    Vibration.wLeftMotorSpeed = static_cast<WORD>(leftVal);
    //    Vibration.wRightMotorSpeed = static_cast<WORD>(rightVal);
    //    // Vibrate the controller
    //    XInputSetState(m_ControllerIndex, &Vibration);
    //}
