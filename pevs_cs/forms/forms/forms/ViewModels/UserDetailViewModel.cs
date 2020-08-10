using System;

using forms.Models;

namespace forms.ViewModels
{
    public class UserDetailViewModel : BaseViewModel
    {
        public User User { get; set; }
        public UserDetailViewModel(User user = null)
        {
            Title = (user == null) ? "My Profile" : user.Name;
            if (user == null) user = DataStore.getMe();
            User = user;
        }
    }
}
