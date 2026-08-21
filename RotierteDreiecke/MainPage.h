#pragma once

#include "MainPage.g.h"

namespace winrt::RotierteDreiecke::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        void StartButton_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        void ClearButton_Click( winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:

        void DrawLine(double x1, double y1, double x2,double y2, winrt::Windows::UI::Xaml::Media::Brush const& brush);
    };
}

namespace winrt::RotierteDreiecke::factory_implementation
{
    struct MainPage :
        MainPageT<MainPage, implementation::MainPage>
    {
    };
}