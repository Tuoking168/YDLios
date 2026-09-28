
-- init
gdeventlistener = init_table_safely(gdeventlistener)
gdceapon.event_listener_in_lua = gdeventlistener

--
-- handle event
--
gdeventlistener.on_cp_event = function(eventName)
	cpnotification.on_cp_event(eventName)
	cpguide.on_cp_event(eventName)
end



