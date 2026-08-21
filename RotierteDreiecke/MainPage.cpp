#include "pch.h"
#include "MainPage.h"

#if __has_include("MainPage.g.cpp")
#include "MainPage.g.cpp"
#endif

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Shapes;

namespace winrt::RotierteDreiecke::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

        
    void MainPage::StartButton_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        DrawCanvas().Children().Clear();
   


        // -----------------------------------------------------
        // Konstanten
        // -----------------------------------------------------

        constexpr double PI =  3.14159265358979323846;

        constexpr int AnzahlDreiecke = 20;


        // -----------------------------------------------------
        // Mittelpunkt des Canvas
        // -----------------------------------------------------

        double mitteX = 300.0;
        double mitteY = 300.0;


        // -----------------------------------------------------
        // Grunddreieck
        //
        // Die Koordinaten beziehen sich zunächst auf
        // den mathematischen Ursprung (0 / 0).
        //
        //
        //               A
        //               *
        //              / \
        //             /   \
        //            /     \
        //           *-------*
        //           B       C
        //
        // -----------------------------------------------------

        double ax = 0.0;
        double ay = -220.0;

        double bx = -100.0;
        double by = 80.0;

        double cx = 100.0;
        double cy = 80.0;


        // -----------------------------------------------------
        // Zufallsfarben vorbereiten
        // -----------------------------------------------------

        std::random_device rd;

        std::mt19937 generator(rd());

        std::uniform_int_distribution<int>
            farbe(0, 255);


        // -----------------------------------------------------
        // 20 Dreiecke
        // -----------------------------------------------------

        for (int i = 0; i < AnzahlDreiecke; i++)
        {
            // ---------------------------------------------
            // Winkel berechnen
            //
            // 360 Grad / 20 = 18 Grad
            //
            // Wir rechnen aber direkt im Bogenmaß:
            //
            // 2 * PI / 20
            // ---------------------------------------------

            double winkel =
                i * (2.0 * PI / AnzahlDreiecke);


            double cosWinkel =
                std::cos(winkel);

            double sinWinkel =
                std::sin(winkel);


            // ---------------------------------------------
            // Punkt A drehen
            // ---------------------------------------------

            double axNeu =
                ax * cosWinkel
                - ay * sinWinkel;

            double ayNeu =
                ax * sinWinkel
                + ay * cosWinkel;


            // ---------------------------------------------
            // Punkt B drehen
            // ---------------------------------------------

            double bxNeu =
                bx * cosWinkel
                - by * sinWinkel;

            double byNeu =
                bx * sinWinkel
                + by * cosWinkel;


            // ---------------------------------------------
            // Punkt C drehen
            // ---------------------------------------------

            double cxNeu =
                cx * cosWinkel
                - cy * sinWinkel;

            double cyNeu =
                cx * sinWinkel
                + cy * cosWinkel;


            // ---------------------------------------------
            // Vom mathematischen Koordinatensystem
            // in das Canvas-Koordinatensystem verschieben
            // ---------------------------------------------

            axNeu += mitteX;
            ayNeu += mitteY;

            bxNeu += mitteX;
            byNeu += mitteY;

            cxNeu += mitteX;
            cyNeu += mitteY;


            // ---------------------------------------------
            // Zufällige Farbe erzeugen
            // ---------------------------------------------

            Windows::UI::Color color;

            color.A = 255;

            color.R =
                static_cast<uint8_t>(
                    farbe(generator));

            color.G =
                static_cast<uint8_t>(
                    farbe(generator));

            color.B =
                static_cast<uint8_t>(
                    farbe(generator));


            SolidColorBrush brush(color);


            // ---------------------------------------------
            // Dreieck aus drei Linien zeichnen
            // ---------------------------------------------

            // A -> B
            DrawLine(axNeu, ayNeu, bxNeu, byNeu, brush);


            // B -> C
            DrawLine(
                bxNeu,
                byNeu,
                cxNeu,
                cyNeu,
                brush);


            // C -> A
            DrawLine(
                cxNeu,
                cyNeu,
                axNeu,
                ayNeu,
                brush);
        }
    }


    // ---------------------------------------------------------
    // Linie zeichnen
    // ---------------------------------------------------------

    void MainPage::DrawLine(
        double x1,
        double y1,
        double x2,
        double y2,
        winrt::Windows::UI::Xaml::Media::Brush const& brush)
    {
        winrt::Windows::UI::Xaml::Shapes::Line line;
        line.X1(x1);
        line.Y1(y1);
        line.X2(x2);
        line.Y2(y2);
        line.Stroke(brush);
        line.StrokeThickness(1.0);

        DrawCanvas().Children().Append(line);
    }


    // ---------------------------------------------------------
    // Löschen
    // ---------------------------------------------------------

    void MainPage::ClearButton_Click(
        winrt::Windows::Foundation::IInspectable const& sender,
        winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
    {
        DrawCanvas()
            .Children()
            .Clear();
    }
}
