using System;
using System.ComponentModel;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

using forms.Models;
using forms.ViewModels;

namespace forms.Views
{
    [DesignTimeVisible(false)]
    public partial class UserDetailPage : ContentPage
    {
        UserDetailViewModel viewModel;

        public UserDetailPage(UserDetailViewModel viewModel)
        {
            InitializeComponent();

            BindingContext = this.viewModel = viewModel;
        }

        public UserDetailPage()
        {
            InitializeComponent();
            viewModel = new UserDetailViewModel();
            BindingContext = viewModel;
        }
    }
}