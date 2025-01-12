using Newtonsoft.Json.Serialization;
using Newtonsoft.Json;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.Serialization.JSON
{
    public class CustomContractResolver : DefaultContractResolver
    {
        public CustomContractResolver()
        {
        }
        protected override JsonProperty CreateProperty(MemberInfo member, MemberSerialization memberSerialization)
        {
            JsonProperty jsonProperty = base.CreateProperty(member, memberSerialization);
            jsonProperty.PropertyName = member.Name;
            return jsonProperty;
        }
    }

}
