using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ManagedModule.JIT.SerClient
{
    [Serializable]
    [AttributeUsage(AttributeTargets.Property, AllowMultiple = false)]
    public sealed class CaptionAttribute : OMAttributeBase
    {
        private string _caption;

        public string Caption
        {
            get
            {
                return _caption;
            }
            set
            {
                if (_caption != value)
                {
                    _caption = value;
                    base.Value = value;
                }
            }
        }

        public CaptionAttribute(string caption)
        {
            _caption = caption;
            base.Value = caption;
        }
    }

}
