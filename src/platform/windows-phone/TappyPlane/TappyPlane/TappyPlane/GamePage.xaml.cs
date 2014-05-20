using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Microsoft.Phone.Tasks;
using System.Diagnostics;
using System.IO.IsolatedStorage;
using FloppyCockComp;
using OpenXLive;
using OpenXLive.Features;

namespace FloppyCock
{
    public partial class MainPage : PhoneApplicationPage
    {
        private Direct3DInterop m_d3dInterop = new Direct3DInterop();
        private object m_d3dContentProvider;
        private bool isAttemptingToSubmitAndOrViewLeaderboard = false;

        public MainPage()
        {
            InitializeComponent();
        }

        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            base.OnNavigatedFrom(e);
        }

        protected override void OnNavigatedTo(System.Windows.Navigation.NavigationEventArgs e)
        {
            base.OnNavigatedTo(e);

            if (XLiveGameManager.CurrentSession != null && XLiveGameManager.CurrentSession.IsValid && XLiveGameManager.CurrentSession.CurrentPlayer != null && !XLiveGameManager.CurrentSession.CurrentPlayer.IsAnonymous)
            {
                if (isAttemptingToSubmitAndOrViewLeaderboard)
                {
                    isAttemptingToSubmitAndOrViewLeaderboard = false;
                    submitBestScoreToLeaderboard();
                }
            }
        }

        protected override void OnBackKeyPress(System.ComponentModel.CancelEventArgs e)
        {
            base.OnBackKeyPress(e);

            if (m_d3dInterop.onBackPressed())
            {
                e.Cancel = true;
            }
        }

        private void DrawingSurface_Loaded(object sender, RoutedEventArgs e)
        {
            // Set window bounds in dips
            m_d3dInterop.WindowBounds = new Windows.Foundation.Size((float)DrawingSurface.ActualWidth, (float)DrawingSurface.ActualHeight);

            // Set native resolution in pixels
            m_d3dInterop.NativeResolution = new Windows.Foundation.Size((float)Math.Floor(DrawingSurface.ActualWidth * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f), (float)Math.Floor(DrawingSurface.ActualHeight * Application.Current.Host.Content.ScaleFactor / 100.0f + 0.5f));

            // Set render resolution to the full native resolution
            m_d3dInterop.RenderResolution = m_d3dInterop.NativeResolution;
            m_d3dInterop.screenType = 1;

            // Hook-up native component to DrawingSurface
            if (m_d3dContentProvider == null)
            {
                m_d3dContentProvider = m_d3dInterop.CreateContentProvider();
            }

            DrawingSurface.SetContentProvider(m_d3dContentProvider);
            DrawingSurface.SetManipulationHandler(m_d3dInterop);

            m_d3dInterop.setWinRtCallback(new WinRtCallback(ProcessCallback));
        }

        async private void ProcessCallback(String command, String param)
        {
            Console.WriteLine("Incoming callback from C++ : " + command);

            if (command.Equals("SHOW_LEADERBOARD"))
            {
                submitBestScoreToLeaderboard();
            }
            else if (command.Equals("GAME_OVER"))
            {
                int score = m_d3dInterop.getScore();

                IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;

                int bestScore = 0;

                if (settings.Contains("BEST_SCORE"))
                {
                    bestScore = Convert.ToInt32(settings["BEST_SCORE"]);
                }

                if (score >= bestScore)
                {
                    if (settings.Contains("BEST_SCORE"))
                    {
                        settings.Remove("BEST_SCORE");
                    }
                    String bestScoreString = Convert.ToString(score);
                    settings.Add("BEST_SCORE", bestScoreString);
                    settings.Save();
                }

                m_d3dInterop.setBestScore(Convert.ToInt32(settings["BEST_SCORE"]));
            }
        }

        private void submitBestScoreToLeaderboard()
        {
            Deployment.Current.Dispatcher.BeginInvoke(() =>
            {
                if (XLiveGameManager.CurrentSession != null && XLiveGameManager.CurrentSession.IsValid && XLiveGameManager.CurrentSession.CurrentPlayer != null && !XLiveGameManager.CurrentSession.CurrentPlayer.IsAnonymous)
                {
                    IsolatedStorageSettings settings = IsolatedStorageSettings.ApplicationSettings;

                    int bestScore = 0;

                    if (settings.Contains("BEST_SCORE"))
                    {
                        bestScore = Convert.ToInt32(settings["BEST_SCORE"]);
                    }

                    if (bestScore > 0)
                    {
                        Leaderboard lb = new Leaderboard(XLiveGameManager.CurrentSession, "c1b8a2f8-6a54-4451-8719-c4a227ed0377");
                        lb.SubmitScore(bestScore);
                    }

                    OpenXLive.Silverlight.XLiveUIManager.ShowLeaderboard();
                }
                else
                {
                    isAttemptingToSubmitAndOrViewLeaderboard = true;
                    OpenXLive.Silverlight.XLiveUIManager.ShowLogon();
                }
            });
        }

        private void OnAdError_ErrorOccurred(object sender, Microsoft.Advertising.AdErrorEventArgs e)
        {
            Debug.WriteLine("AdControl error: " + e.Error.Message);
            AdUnit.Height = 0;
            AdUnit.Visibility = System.Windows.Visibility.Collapsed;
        }
    }
}