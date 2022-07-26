require 'toxiproxy'

Toxiproxy.populate([
  {
    name: "aby3_party_1",
    listen: "127.0.0.1:50010",
    upstream: "127.0.0.1:50011"
  },

	{
    name: "aby3_party_2",
    listen: "127.0.0.1:50020",
    upstream: "127.0.0.1:50022"
  	},

{

    name: "aby3_party_3",
    listen: "127.0.0.1:50030",
    upstream: "127.0.0.1:50033"
  }

])

