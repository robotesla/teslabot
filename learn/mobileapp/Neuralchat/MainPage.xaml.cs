using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using Neuralchat.Models;

namespace Neuralchat
{
    public partial class MainPage : ContentPage
    {
        public ObservableCollection<Message> messages = new ObservableCollection<Message> { new Message { Body = "Привет!", Sender = "Нейронная сеть" } };
        public MainPage()
        {
            InitializeComponent();
            messagesList.ItemsSource = messages;
        }

        void Handle_Completed(object sender, System.EventArgs e)
        {
            DisplayAlert("классно", "работает", "OKEE");
        }
    }
}
