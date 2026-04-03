#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include "PlayerEngine.h"

using namespace winrt;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::Media_Player::implementation
{
    PlayerEngine player;

    void MainWindow::OnOpenFile(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        bool isOpen = player.OpenFile(L"C:/Users/vanec/Media_Player/Media_Player/files/video.mp4");

        assert(isOpen);
    }

    void MainWindow::OnPlayPause(winrt::Windows::Foundation::IInspectable const& sender, winrt::Microsoft::UI::Xaml::RoutedEventArgs const& args)
    {
        
    }
}
