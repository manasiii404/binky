$(document).ready(function() {
    console.log('Project Portfolio Loaded with jQuery');

    // Handle navigation button clicks
    $('.nav-btn').on('click', function() {
        // Get the target section
        const targetSection = $(this).data('section');
        
        // Remove active class from all buttons
        $('.nav-btn').removeClass('active');
        
        // Add active class to clicked button
        $(this).addClass('active');
        
        // Hide all sections with fade out
        $('.section').removeClass('active').fadeOut(200);
        
        // Show target section with fade in
        setTimeout(function() {
            $('#' + targetSection).addClass('active').fadeIn(400);
        }, 200);
    });

    // Add hover effect to project cards
    $('.project-card').hover(
        function() {
            $(this).find('.badge').css({
                'transform': 'scale(1.05)',
                'transition': 'transform 0.3s ease'
            });
        },
        function() {
            $(this).find('.badge').css({
                'transform': 'scale(1)',
                'transition': 'transform 0.3s ease'
            });
        }
    );

    // Add click animation to project cards
    $('.project-card').on('click', function() {
        $(this).css({
            'transform': 'scale(0.98)',
            'transition': 'transform 0.1s ease'
        });
        
        setTimeout(() => {
            $(this).css({
                'transform': '',
                'transition': 'transform 0.3s ease'
            });
        }, 100);
    });

    // Animate tags on hover
    $('.tag').hover(
        function() {
            $(this).css({
                'background': 'rgba(255, 255, 255, 0.3)',
                'transform': 'translateY(-2px)',
                'transition': 'all 0.2s ease'
            });
        },
        function() {
            $(this).css({
                'background': 'rgba(255, 255, 255, 0.2)',
                'transform': 'translateY(0)',
                'transition': 'all 0.2s ease'
            });
        }
    );
});
