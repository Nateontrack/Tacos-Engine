#pragma once

namespace dae
{
    class XBox360Controller final
    {
    public:
        enum class ControllerButton
        {
            DPadUp = 0x0001,
            DPadDown = 0x0002,
            DPadLeft = 0x0004,
            DPadRight = 0x0008,
            Start = 0x0010,
            Back = 0x0020,
            LeftThumb = 0x0040,
            RightThumb = 0x0080,
            LeftShoulder = 0x0100,
            RightShoulder = 0x0200,
            ButtonA = 0x1000,
            ButtonB = 0x2000,
            ButtonX = 0x4000,
            ButtonY = 0x8000
        };
        
        void Update();

        static bool IsConnected(int controllerIndex);

        bool IsDown(ControllerButton button) const;
        bool IsUp(ControllerButton button) const;
        bool IsPressed(ControllerButton button) const;

        unsigned int GetIndex() const;
        void SetActive(bool active);

        explicit XBox360Controller(unsigned int controllerIndex);
        ~XBox360Controller();

    private:
        class XBox360ControllerImpl; //needs to be declared in class for pImpl to work
        XBox360ControllerImpl* m_pImpl;
    };
}



