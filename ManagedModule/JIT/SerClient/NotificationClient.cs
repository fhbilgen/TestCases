using ManagedModule.JIT.Serialization.JSON;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    public class NotificationClient
    {
        public NotificationClient()
        {
        }



        public void SendNotification(string topic, DTORequestLog dtoLog = null, DTORequestLogDetail dtoDetail = null)
        {            
            string data = string.Empty;
            try
            {
                if (dtoLog != null)
                {
                    dtoLog.RecordDate = Calendar.GetAppDateTime();
                    dtoLog.RecordBranchCode = CallerInformation.BranchCode;
                    dtoLog.RecordScreenCode = CallerInformation.ScreenCode;
                    dtoLog.RecordRequestObjectId = CallerInformation.RequestObjectId;
                    dtoLog.RecordChannelCode = CallerInformation.Channel;
                    dtoLog.RecordUserCode = CallerInformation.UserCode;
                    data = "{\"TopicName\":\"" + topic + "\",\"Message\":" + SerializeWithPropertyName(dtoLog).ToString() + "}";
                }
                else if (dtoDetail != null)
                {
                    dtoDetail.RecordDate = Calendar.GetAppDateTime();
                    dtoDetail.RecordBranchCode = CallerInformation.BranchCode;
                    dtoDetail.RecordScreenCode = CallerInformation.ScreenCode;
                    dtoDetail.RecordRequestObjectId = CallerInformation.RequestObjectId;
                    dtoDetail.RecordChannelCode = CallerInformation.Channel;
                    dtoDetail.RecordUserCode = CallerInformation.UserCode;
                    data = "{\"TopicName\":\"" + topic + "\",\"Message\":" + SerializeWithPropertyName(dtoDetail).ToString() + "}";
                }
                dynamic val = JSONSerializer.DeserializeObject<object>(data);
                //kafkaProducer.ProduceMessageAsync(val, true);
            }
            catch
            {
                LogManager.Log("KafkaNotificationSendConverter", topic, "basarisiz", "KafkaServis", "Fiyatlama");
            }
        }
    }
}
