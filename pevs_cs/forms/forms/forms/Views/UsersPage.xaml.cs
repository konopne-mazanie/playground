using System;
using System.ComponentModel;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using Xamarin.Forms.Xaml;

using forms.Models;
using forms.Views;
using forms.ViewModels;

namespace forms.Views
{
    // Learn more about making custom code visible in the Xamarin.Forms previewer
    // by visiting https://aka.ms/xamarinforms-previewer
    [DesignTimeVisible(false)]
    public partial class UsersPage : ContentPage
    {
        UsersViewModel viewModel;

        public UsersPage()
        {
            InitializeComponent();

            BindingContext = viewModel = new UsersViewModel();
        }

        async void OnItemSelected(object sender, SelectedItemChangedEventArgs args)
        {
            var item = args.SelectedItem as User;
            if (item == null)
                return;

            await Navigation.PushAsync(new UserDetailPage(new UserDetailViewModel(item)));

            // Manually deselect item.
            ItemsListView.SelectedItem = null;
        }

        protected override void OnAppearing()
        {
            base.OnAppearing();

            if (viewModel.Users.Count == 0)
                viewModel.LoadUsersCommand.Execute(null);
        }
    }
}