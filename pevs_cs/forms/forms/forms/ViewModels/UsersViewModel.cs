using System;
using System.Collections.ObjectModel;
using System.Diagnostics;
using System.Threading.Tasks;

using Xamarin.Forms;

using forms.Models;
using forms.Views;

namespace forms.ViewModels
{
    public class UsersViewModel : BaseViewModel
    {
        public ObservableCollection<User> Users { get; set; }
        public Command LoadUsersCommand { get; set; }

        public UsersViewModel()
        {
            Title = "People";
            Users = new ObservableCollection<User>();
            LoadUsersCommand = new Command(async () => await ExecuteLoadItemsCommand());
        }

        async Task ExecuteLoadItemsCommand()
        {
            if (IsBusy)
                return;

            IsBusy = true;

            try
            {
                Users.Clear();
                var items = await DataStore.GetItemsAsync(true);
                foreach (var item in items)
                {
                    Users.Add(item);
                }
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex);
            }
            finally
            {
                IsBusy = false;
            }
        }
    }
}