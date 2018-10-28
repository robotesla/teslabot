using System;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Xamarin.Forms;
using Neuralchat.Models;
using System.Net;
using System.Net.Http;

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

        async void Handle_Completed(Entry sender, System.EventArgs e)
        {
            if (sender.Text != "") {
                messages.Add(new Message { Body = sender.Text, Sender = "Пользователь" });
                try
                {
                    this.Title = "Получение ответа...";
                    string responce = await GetResponceFromNeuralNetwork(sender.Text);
                    messages.Add(new Message { Body = responce, Sender = "Нейронная сеть" });
                    this.Title = "Обучение нейросети";
                    sender.Text = String.Empty;
                }
                catch (Exception)
                {
                    await DisplayAlert("Ошибка", "Произошла ошибка получения ответа.", "OK");
                }
            }
        }

        public async Task<string> GetResponceFromNeuralNetwork(string body)
        {
            var httpClient = new HttpClient();
            Task<string> contentsTask = httpClient.GetStringAsync("http://192.168.0.101:5000/api_v1/learning/get_responce?body=" + body); // async method!
            string contents = await contentsTask;
            return contents;
        }
    }
}
